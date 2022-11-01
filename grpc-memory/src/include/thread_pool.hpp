#pragma once
#include <semaphore.h>

#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool
{
    using Task = std::function<void()>;
    std::vector<std::thread> pool;
    std::queue<Task> tasks;
    std::mutex m_lock;
    sem_t sem_;
    // std::condition_variable cv_task;
    std::atomic<bool> stoped;
    std::atomic<int>  taskNum;
    std::atomic<int>  idlThrNum;
    const int op_ = 1000;

public:
    bool wait(int tv_msec){
        struct timespec ts;
        if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
            return false;
        }
        ts.tv_sec += (tv_msec / op_);
        ts.tv_nsec += (tv_msec % op_ * 1000 * 1000);
        return sem_timedwait(&sem_, &ts) == 0;
    }

    inline ThreadPool(unsigned short size = 4) :stoped{ false }
    {
        static int wait_for_job_count = 0;
        sem_init(&sem_, 0, 0);
        taskNum = 0; 
        idlThrNum = size < 1 ? 1 : size;
        for (size = 0; size < idlThrNum; ++size)
        {   
            pool.emplace_back(
                [this]
                { 
                    while(!this->stoped)
                    {
                        std::function<void()> task;
                        {   
                            while(this->wait(1000) == false){
                                if (this->stoped)
                                    return;
                                if(wait_for_job_count++ % 100 == 0){
                                    std::cout << "wait for job..." << std::endl;
                                }
                            }
                            
                            std::unique_lock<std::mutex> lock{ this->m_lock };
                            
                            task = std::move(this->tasks.front()); // 取一个 task
                            this->tasks.pop();
                            taskNum = this->tasks.size();
                        }
                        idlThrNum--;
                        task();
                        idlThrNum++;
                    }
                }
            );
        }
    }
    inline ~ThreadPool()
    {
        stoped.store(true);
        // cv_task.notify_all();
        for (std::thread& thread : pool) {
            if(thread.joinable())
                thread.join(); 
        }
    }

public:
    template<class F, class... Args>
    auto commit(F&& f, Args&&... args) ->std::future<decltype(f(args...))>
    {
        if (stoped.load())   
            throw std::runtime_error("commit on ThreadPool is stopped.");

        using RetType = decltype(f(args...)); 
        auto task = std::make_shared<std::packaged_task<RetType()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );   
        std::future<RetType> future = task->get_future();
        {   
            std::lock_guard<std::mutex> lock{ m_lock };
            tasks.emplace(
                [task]()
                { 
                    (*task)();
                }
            );
            sem_post(&sem_);
        }
        return future;
    }
    int idlCount() { return idlThrNum; }

    int taskCount() { return taskNum;}
};