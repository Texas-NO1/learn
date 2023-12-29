#include <iostream>
#include <malloc.h>

struct Test {
    int x;
    // void* operator new(unsigned long s) { // 补充： 为什么不用对象就可以调用，因为operator new和delete重载默认就是static的
    //     std::cout << "使用重载new函数" << std::endl;
    //     return malloc(s);
    // }
    // void* operator new(unsigned long s, void *ptr) {
    //     std::cout << "使用重载new函数ptr" << std::endl;
    //     return ptr;
    // }
    // void operator delete(void *p, unsigned long s) { // 优先级低
    //     std::cout << "使用重载delete函数，释放" << s << "字节大小" << std::endl;
    //     return free(p);
    // }
    // void operator delete(void *p) { // 优先级高
    //     std::cout << "使用重载delete函数" << std::endl;
    //     return free(p);
    // }
    Test() {
        std::cout << "Test construct" << std::endl;     
    };
    ~Test() {
        std::cout << "Test destruct" << std::endl;
    };
};
void* operator new(std::size_t s) {
    // std::cout << "使用全局重载new函数" << std::endl;
    return malloc(s);
}
// void test() {

// }
// void test() {
    
// }
// void* operator new(unsigned long s, void *ptr) {
//     // std::cout << "使用重载new函数" << std::endl;
//     return ptr;
// }
// void operator delete(void *p, unsigned long s) {
//     std::cout << "使用全局重载delete函数" << std::endl;
//     return free(p);
// }
int main () {
    // Test t;
    Test *t = new Test();
    t->x = 10;
    // Test *ttemp = new(t) Test();
    // std::cout << ttemp->x << std::endl;
    // // delete t;
    // // char t[10];
    // new(t) Test();
    // delete t;
    return 0;
}