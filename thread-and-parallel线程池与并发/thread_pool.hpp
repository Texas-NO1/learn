#include <thread>
#include <condition_variable>
#include <vector>
#include <queue>
#include <future>
#include <functional>

class Semaphore {
public:
    Semaphore(int cnt = 0) : sem_(cnt) {}
    void wait() {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this]{return this->sem_ > 0;});
        --sem_;
    }

    bool wait_for(int milliseconds) {
        std::unique_lock<std::mutex> lock(mtx_);
        bool wait_res = cv_.wait_for(lock, std::chrono::milliseconds(milliseconds), [this]{return this->sem_ > 0;});
        if (wait_res) --sem_;
        return wait_res;
    }

    void signal() {
        {
            std::unique_lock<std::mutex> lock(mtx_);
            ++sem_;
        }
        cv_.notify_one();
    }

    int sem() {
        return sem_;
    }

private:
    std::mutex mtx_;
    int sem_;
    std::condition_variable cv_;
};

class ThreadPool {
public:
    ThreadPool(int pool_size) {
        sem_ = new Semaphore(); // 可以用虚继承实现不同版本信号量
        running_.store(true);
        pool_size = pool_size > 0 ? pool_size : 1;
        pool_size_ = pool_size;
        idl_cnt_ = pool_size;
        for (int i = 0; i < pool_size_; ++i) {
            pool_.emplace_back(std::thread(&ThreadPool::block_waiting, this));
        }
    }
    // 类似std::thread构造函数
    template<typename Callable, typename... Args>
    auto commit(Callable&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        auto task = std::make_shared<std::packaged_task<decltype(f(args...))()>>(std::bind(f, args...));
        {
            std::unique_lock<std::mutex> lock(task_mtx_);
            tasks_.emplace([task]{(*task)();});
            sem_->signal();
        }
        return task->get_future();
    }
    ~ThreadPool() {
        running_.store(false);
        for (auto &&t : pool_) {
            if (t.joinable()) t.join();
        }
        if (sem_) delete sem_;
    }
private:
    std::atomic<int> pool_size_;
    std::atomic<int> idl_cnt_;
    std::atomic<bool> running_;
    std::mutex task_mtx_;
    std::queue<std::function<void()>> tasks_;
    std::vector<std::thread> pool_;
    Semaphore *sem_;

    // 阻塞等待获取task
    void block_waiting() {
        while (running_) {
            while(sem_->wait_for(1000) == false) { // 每1秒判断是否已不再运行
                if (running_) continue;
                return;
            }
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(task_mtx_);
                task = std::move(tasks_.front());
                tasks_.pop();
            }
            idl_cnt_--;
            task();
            idl_cnt_++;
        }
    }
};