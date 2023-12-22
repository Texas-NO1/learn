#include <iostream>

// decltype判断表达式或对象类型，可以用于自动判断返回值类型
auto test(int x) -> decltype(x) {
    return x;
}

struct T {
    int x;
};

int main () {
    T t;
    // 判断对象类型
    decltype(t) x;
    // 判断表达式类型
    decltype(1 + 0.23) y;
    // auto->dec
    test(10);
    return 0; 
}