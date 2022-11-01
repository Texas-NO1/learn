#include <iostream>

void test(void *) { // 参数名可以为空
    std::cout << "F1 test(void *)" << std::endl;
}

void test(int = 10) { // 还可以有默认值
    std::cout << "F2 test(int = 10)" << std::endl;
}

// 普通函数
void test(int x, int * = static_cast<int*>(0)) { // 参数名可以为空，但感觉没啥意义
    std::cout << "F3 test(int x, void * = static_cast<void*>(0))" << std::endl;
}
// 模版
template<typename T1, typename T2>
auto test(T1 t1, T2 t2) -> decltype(t1 + t2) {
    std::cout << "F4 template<typename T1, typename T2>test(T1 t1, T2 t2)" << std::endl;
    return t1 + t2;
}

// 特化
template<> 
auto test(int a, int b) -> int {
    std::cout << "F5 template<>test(int a, int b)" << std::endl;
    return a + b;
}

// 普通函数
auto test(int a, int b) -> int {
    std::cout << "F6 test(int a, int b)" << std::endl;
    return a + b;
}

decltype(auto) test(int x, int y, int z) {
    return void();
}

int main () {

    int x = 0;
    test();
    test(&x);
    test(x, &x);
    test(x, x); // 调用优先级: 普通方法 > 模版方法
    return 0;
}