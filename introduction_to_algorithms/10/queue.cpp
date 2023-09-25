#include <iostream>
#include <vector>
#include <thread>

// head == tail时为空
// tail + 1 = head时为满

template<class T>
struct Queue {
    std::vector<T> data;
    int head;
    int tail;
    Queue(int size = 1000) {
        data.resize(size);
        head = tail = 0;
    }
    bool empty() {
        return head == tail;
    }
    bool full() {
        return tail + 1 == head;
    }
    void enqueue(const T &&x) {
        if (full()) throw std::runtime_error("overflow");
        data[tail] = x;
        if (tail == data.size() - 1) {
            tail = 0;
        } else {
            tail++;
        }
    }
    T dequeue() {
        if (empty()) throw std::runtime_error("underflow");
        T x = data[head];
        if (head == data.size() - 1) {
            head = 0;
        } else {
            head++;
        }
        return x;
    }
};

int main () {
    Queue<int> q;
    std::cout << q.empty() << std::endl;
    q.enqueue(1);
    std::cout << q.empty() << std::endl;
    q.dequeue();
    std::cout << q.empty() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    q.dequeue(); // test error exit
    std::cout << q.empty() << std::endl;
    return 0;
}