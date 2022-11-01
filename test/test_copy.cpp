#include <iostream>
#include <string>

struct Test {
    Test() {
        std::cout << "con" << std::endl;
    };
    Test(const Test &t) {
        std::cout << "copy con" << std::endl;
    }
    Test(const Test &&t) {
        std::cout << "move copy con" << std::endl;
    }
    ~Test() {
        std::cout << "destory" << std::endl;
    }
};

int main () {
    std::string s;
    Test t;
    Test at(t);
    Test at1(std::move(t));
    return 0;
}