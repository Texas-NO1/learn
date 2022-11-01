// #pragma pack(4)
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <new>
#include <vector>
// #pragma pack(4)

struct test {
    int x;
};

struct alignas(32) T {
    int x;
};

struct Test {
    int x; // 4
    double y; // 8
};

// void* operator new(size_t s, std::align_val_t t) {
//     printf("%d, %d\n", s, t);
//     return malloc(s);
// }

// void* operator new(size_t s) {
//     printf("%d\n", s);
//     return malloc(s);
// }


int main () {
    // printf("%d\n", __STDCPP_DEFAULT_NEW_ALIGNMENT__);

    // test *y = new test(); // 4

    // test *x = new(std::align_val_t(32)) test(); // 32

    // T *x = new T();


    


    // T *x = new(std::align_val_t(32)) T();
    // std::cout << sizeof(test) << std::endl;
    // std::cout << sizeof(T) << std::endl;
    // printf("%d", sizeof(T));
    return 0;
}

// int main () {
//     T *t = new T();
//     printf("%d\n", alignof(T));
//     return 0;
// }