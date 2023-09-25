#include <iostream>
#include <vector>
#include <thread>

template<class T>
struct Stack {
    std::vector<T> data;
    int top;
    Stack(int size = 1000) {
        data.resize(size);
        top = 0;
    }
    bool empty() {
        return top == 0;
    }
    void push(const T &&x) {
        top++;
        data[top] = x;
    }
    T pop() {
        if (empty()) throw std::runtime_error("underflow");
        else {
            top--;
            return data[top + 1];
        }
    }
};

int main () {
    Stack<int> s;
    std::cout << s.empty() << std::endl;
    s.push(123);
    std::cout << s.empty() << std::endl;
    s.pop();
    std::cout << s.empty() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    s.pop(); // test error exit
    std::cout << s.empty() << std::endl;
    return 0;
}