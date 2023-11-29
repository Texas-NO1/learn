#include <semaphore.h>
#include <iostream>
#include <thread>


class Semaphore {
public:
    Semaphore(int cnt = 0) {
        sem_init(&sem_, 0, cnt); // 第二个参数>0时表示进程间共享的信号量，TODO实验
    }
    void wait() {
        sem_wait(&sem_);
    }

    bool wait_for(int milliseconds) {
        timespec t;
        if (clock_gettime(CLOCK_REALTIME, &t) != 0) {
            return false;
        }
        t.tv_sec += milliseconds / 1000;
        t.tv_nsec += milliseconds % 1000 * 1000 * 1000;
        return sem_timedwait(&sem_, &t) == 0;
    }

    void signal() {
        sem_post(&sem_);
    }

    int sem() {
        int val;
        sem_getvalue(&sem_, &val);
        return val;
    }

    void output() {
        std::cout << "semaphore " << sem() << std::endl;
    }

private:
    sem_t sem_;
};

int main () {
    Semaphore sem;
    std::thread wait_thread([&]{
        std::cout << "wait for sem" << std::endl;
        sem.output();
        // sem.wait_for(500);
        sem.wait();
        sem.output();
        std::cout << "wait done" << std::endl;
    });
    std::cout << "sleep 10s to signal" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    sem.signal();
    sem.output();
    std::cout << "sigal done" << std::endl;
    if (wait_thread.joinable()) wait_thread.join();
    return 0;
}