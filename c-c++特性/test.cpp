#include <iostream>

class Base {
public:
    uint64_t x;
    void A() {printf("Base A\n");} // 编译时确定
    virtual void B() {printf("Base B\n");} //运行时确定 
    virtual void C() {printf("Base C %d\n", this->x);} //运行时确定 
    virtual void D(int y) {printf("Base D %d %d\n", this->x, y);} 
};

// class Base1 {
// public:
//     uint64_t x;
//     void A() {printf("Base1 A\n");} // 编译时确定
//     virtual void B() {printf("Base1 B\n");} //运行时确定 
//     virtual void C() {printf("Base1 C %d\n", this->x);} //运行时确定 
//     virtual void D(int y) {printf("Base1 D %d %d\n", this->x, y);} 
// };

class Extend1 : public Base {
public:
    void A() {printf("Extend1 A\n");} // 隐藏（重定义）
    // void B() {printf("Extend1 B\n");} // 重写，只有父类的函数为虚函数时才算重写，子类可以省略virtual关键字
    virtual void E() {printf("Extend1 B\n");} // 重写，只有父类的函数为虚函数时才算重写，子类可以省略virtual关键字
    void B(int x) {printf("Extend1 B(int)\n");} // 重载
};

class Extend2 : public Base {
public:
    void A() {printf("Extend2 A\n");} // 隐藏（重定义）
    void C() {printf("Extend2 C %d\n", x);}// 重写，只有父类的函数为虚函数时才算重写
    void B() {printf("Extend2 B\n");} // 重写，只有父类的函数为虚函数时才算重写
    virtual void D() {printf("Extend2 D\n");} // 新建
};

class Normal {
public:
    uint64_t x;
};

void testAllFunc(Base *base) {
    printf("type : %s\n", typeid(base).name());
    base->A();
    base->B();
}

int main () {
    // Base1 e;

    // uint64_t test[2];
    // Base *base = new(test) Base();
    // base->x = 100;
    // printf("Base vptr : %p\n", test[0]);
    // for (int i = 0; i < 3; ++i) {
    //     printf("func %d = %p\n", i, *((uint64_t*)(test[0]) + i));
    // }

    // Extend1 *extend1 = new(test) Extend1();
    // printf("Extend1 vptr : %p\n", test[0]);
    // for (int i = 0; i < 4; ++i) {
    //     printf("func %d = %p\n", i, *((uint64_t*)(test[0]) + i));
    // }
    char a0;
    int a1;
    char a2;
    int a3;
    char a4;
    int a5;
    printf("%p\n", &a0);
    printf("%p\n", &a1);
    printf("%p\n", &a2);
    printf("%p\n", &a3);
    printf("%p\n", &a4);
    printf("%p\n", &a5);

    printf("%d\n", (uint64_t)&a0 - (uint64_t)&a1);
    printf("%d\n", (uint64_t)&a1 - (uint64_t)&a2);
    printf("%d\n", (uint64_t)&a2 - (uint64_t)&a3);
    printf("%d\n", (uint64_t)&a3 - (uint64_t)&a4);
    printf("%d\n", (uint64_t)&a4 - (uint64_t)&a5);
    return 0;
}