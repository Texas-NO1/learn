#include <iostream>
#include <malloc.h>

struct Test {
    int x;
};

void* operator new(std::size_t s) {
    std::cout << "use override new" << std::endl;
    return ::operator new(s); // 在这里::operator new已经被替换成了当前环境下的operator new，所以会不断循环调用自身
}

int main () {
    Test *t = new Test();
    return 0;
}