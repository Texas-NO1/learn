#include <condition_variable>
#include <iostream>
#include <thread>

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

    void output() {
        std::cout << "semaphore " << sem_ << std::endl;
    }

private:
    std::mutex mtx_;
    int sem_;
    std::condition_variable cv_;
};

int main () {
    Semaphore sem;
    std::thread wait_thread([&]{
        std::cout << "wait for sem" << std::endl;
        sem.wait_for(500);
        std::cout << "wait done" << std::endl;
    });
    std::cout << "sleep 10s to signal" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    sem.signal();
    std::cout << "sigal done" << std::endl;
    if (wait_thread.joinable()) wait_thread.join();
    return 0;
}