#include <iostream>

class OnlyHeap {
private:
    ~OnlyHeap() {};
public:
    OnlyHeap() {};
};

class OnlyStack {
private:
    void* operator new(std::size_t size) {return malloc(size);};
    void operator delete(void *ptr) {};
public:
    OnlyStack() {};
    ~OnlyStack() {};
};

int main () {
    // OnlyHeap oh; // 错误：析构函数为私有成员函数
    OnlyHeap *oh = new OnlyHeap();
    // delete oh; // 错误：析构函数为私有成员函数

    // OnlyStack *os = new OnlyStack(); // 错误：new为private，无法调用
    OnlyStack os;
    return 0;
}