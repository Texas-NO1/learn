#include <iostream>
#include <memory>
#include <unistd.h>

// 正常运行
void testHeap(std::shared_ptr<int> &ptr) {
    int *t = new int(10);
    ptr = std::shared_ptr<int>(t);
}

// 报错，free失败，double free/invalid pointer
void testStack(std::shared_ptr<int> &ptr) {
    int t = 10; // 这个对象的内存在方法结束后就结束了
    ptr = std::shared_ptr<int>(&t);
}

int main () {
    int test;
    std::shared_ptr<int> ptr;
    testStack(ptr);
    if (ptr) {
        std::cout << ptr.use_count() << " " << *ptr << std::endl;
    }
    return 0;
}