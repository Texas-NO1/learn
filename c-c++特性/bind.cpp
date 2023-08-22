#include <functional>
#include <iostream>

void test(int x) {
    std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << " " << x << std::endl;
}

class Test {
public:
    void test(int x) {
        std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << " " << x << std::endl;
    }
};

int main() {
    // bind 全局函数
    auto t1 = std::bind(&test, 1);
    // mem_fn 成员函数。声明时无法传入对象与参数；调用时需要传入对象与参数
    auto t2 = std::mem_fn(&Test::test);
    // bind 成员函数。声明时可以传入对象与参数（对象预先定义）；也可以使用占位符在调用时再传入对象与参数（对象延迟定义）
    Test t;
    auto t3 = std::bind(&Test::test, &t, 3);
    auto t4 = std::bind(&Test::test, std::placeholders::_1, std::placeholders::_2);
    t1();
    t2(t, 2);
    t3();
    t4(t, 4);
    return 0;
}