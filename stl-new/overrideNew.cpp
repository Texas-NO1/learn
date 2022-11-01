#include <vector>
#include <malloc.h>
#include <iostream>

void* operator new(std::size_t s) {
    std::cout << "alloc " << s << std::endl;
    return malloc(s);
}

void* operator new[](std::size_t s) {
    std::cout << "alloc[] " << s << std::endl;
    return malloc(s);
}

void operator delete(void* ptr) {
    std::cout << "free " << std::endl;
    free(ptr);
}

void operator delete[](void* ptr) {
    std::cout << "free[] " << std::endl;
    free(ptr);
}

int main () {
    // std::basic_string<long> s;
    // s.c_str();
    // // for (int i = 0; i < 1000; i++) {
    // //     vec.push_back(i + 1000000000);
    // // }
    int *x = new int[100];
    std::cout << *(x - 1) << std::endl;
    return 0;
}