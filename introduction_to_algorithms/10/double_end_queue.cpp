#include <iostream>
#include <vector>
#include <thread>
#include <queue>

// 双端队列
// head == tail时为满
// head + 1 = tail时为空

template<class T>
struct Queue {
    std::vector<T> data;
    int head;
    int tail;
    Queue(int size = 1000) {
        data.resize(size);
        head = 0;
        tail = 1;
    }
    bool empty() {
        return head + 1 == tail;
    }
    bool full() {
        return head == tail;
    }
    void rpush(const T &&x) {
        if (full()) throw std::runtime_error("overflow");
        data[tail] = x;
        if (tail == data.size() - 1) {
            tail = 0;
        } else {
            tail++;
        }
    }
    void lpush(const T &&x) {
        if (full()) throw std::runtime_error("overflow");
        data[head] = x;
        if (head == 0) {
            head = data.size() - 1;
        } else {
            head--;
        }
    }
    T rpop() {
        if (empty()) throw std::runtime_error("underflow");
        if (tail == 0) {
            tail = data.size() - 1;
        } else {
            tail--;
        }
        return data[tail];
    }
    T lpop() {
        if (empty()) throw std::runtime_error("underflow");
        if (head == data.size() - 1) {
            head = 0;
        } else {
            head++;
        }
        return data[head];
    }
};

int main () {
    Queue<int> q;
    std::cout << q.empty() << std::endl;
    q.rpush(1);
    std::cout << q.empty() << std::endl;
    q.lpop();
    std::cout << q.empty() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    q.rpop(); // test error exit
    std::cout << q.empty() << std::endl;
    return 0;
}