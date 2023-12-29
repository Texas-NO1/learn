#include <iostream>

void test(std::string &&org) {
    std::string move = std::move(org);
    std::cout << "in test move to: " << move << std::endl;
}

int main () {
    std::string x = "i am string";
    std::string &y = x; // 左值引用，常规引用
    std::cout << "org: " << x << std::endl;
    std::cout << "lref: " << y << std::endl;
    std::cout << std::endl;
    std::string z = std::move(x); // 右值引用，移动构造，不需要进行深拷贝
    std::cout << "org: " << x << std::endl;
    std::cout << "rref: " << z << std::endl;
    std::cout << std::endl;

    test(std::move(z));
    std::cout << "org: " << z << std::endl;
    std::cout << std::endl;
    return 0;
}