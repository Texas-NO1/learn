#include <new>
#include <iostream>
struct Test {
    int x; // 4字节 
    Test() {
        printf("construct");
    };
    ~Test() {
        printf("destruct");
    };
};

int main () {
    // step 1
    void *origin = ::operator new(sizeof(Test) * 2); // ::表示使用顶层命名空间，new函数
    printf("%p\n", origin);
    char *temp = (char*)origin;
    for (int i = 0; i < sizeof(Test) * 2; ++i) {
        temp[i] = '0' + i;
    }

    // step 2
    void *ptr = ::operator new(sizeof(Test), origin); // 直接利用t的前sizeof(Test)个已开辟的字节
    printf("%p\n", ptr);
    char *temp_ptr = (char *)ptr;
    for (int i = 0; i < sizeof(Test); ++i) {
        printf("%c", temp_ptr[i]); // 结果为0123的字符串，对应的16进制分别为30,31,32,33
    }
    printf("\n");

    // step 3
    Test* test = (Test*)ptr;
    printf("%d\n", test->x); // 0x33323130 （小端模式）

    // // step 4
    ::operator delete(origin, sizeof(Test)); // 第二个参数没用，free()函数并不需要指定size（可能仅用来输出debug），无论多少都不会存在内存泄漏问题
    ::operator delete(origin); // double free
    return 0;
}