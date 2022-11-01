#include <iostream>
#include <type_traits>

// Plain Old Data(POD)类型
// https://blog.csdn.net/Jxianxu/article/details/80524526

#pragma pack(1)

class A1 {};
class A2 {};

class B1 : public A1 { // 10 字节，非POD类型。c++能够让子类和父类共享相同起始地址（直接转换），但由于父类没有成员，且由于c++标准要求相同类型的对象的地址必须不相同，所以必须另外开1字节存放基类A1
public:
    A1 a1;
    double x;
};

class B2 : public A2 { // 9 字节，POD类型
public:
    A1 a1;
    double x;
};


int main () {
    B1 b1;
    std::cout << sizeof(B1) << ", " << std::is_pod<B1>::value <<  std::endl;
    std::cout << "b1 start " << &b1 << " b1.a1 start" << &(b1.a1) << std::endl;


    B2 b2;
    std::cout << sizeof(B2) << ", " << std::is_pod<B2>::value <<  std::endl;
    std::cout << "b2 start " << &b2 << " b2.a1 start" << &(b2.a1) << std::endl;
    return 0;
}