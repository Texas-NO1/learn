#include <iostream>

struct Test {
private:
    int x;
public:
    explicit Test() {
        std::cout << "construct 1" << std::endl;
    }

    explicit Test(int x) {
        this->x = x;
        std::cout << "construct 2" << std::endl;
    }
};

int main () {

    // Test x;// 正确，不需要写()

    // Test y = {10}; // 错误，{10}无法被转换成Test(10)

    return 0;
}