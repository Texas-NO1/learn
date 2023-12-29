#include <iostream>

void print(std::string str) {
    std::cout << str << std::endl;
}

class A {
public:
    A() {print(__FUNCTION__);}
    ~A() {print(__FUNCTION__);}
};

class B {
public:
    B() {print(__FUNCTION__);}
    ~B() {print(__FUNCTION__);}
};

class C {
private:
    A a;
    B b;
public:
    C() {print(__FUNCTION__);}
    ~C() {print(__FUNCTION__);}
};

class D {
private:
    A a;
    B b;
public:
    // 初始化列表顺序不重要，一定是按照声明顺序来初始化的 a->b
    D() : b(), a() {print(__FUNCTION__);}
    ~D() {print(__FUNCTION__);}
};

class E {
private:
    A &a;
    const B b;
public:
    E(A &sA, B &sB) : a(sA), b(sB) {
        // a = sA; // 错误：引用类型必须在初始化列表中初始化
        // b = sB; // 错误：const类型必须在初始化列表中初始化
        print(__FUNCTION__);
    }
    ~E() {print(__FUNCTION__);}
};

class F {
private:
    int x;
public:
    F(int x) : x(x) {print(__FUNCTION__);};
    ~F() {print(__FUNCTION__);}
};

class G {
private:
    F f;
public:
    // G() {print(__FUNCTION__);} // 错误：没有构造F，因为F没有默认构造函数
    // G() {f = F(10); print(__FUNCTION__);};  // 错误：没有构造函数的成员必须在初始化列表中构造
    G() : f(10) {print(__FUNCTION__);}// 没有构造函数的成员必须在初始化列表中构造
    ~G() {print(__FUNCTION__);}
};

class H {
private:
    int x;
public:
    H() {print(__FUNCTION__);};
    H(int x) : x(x) {print(__FUNCTION__);};
    ~H() {print(__FUNCTION__);}
};

class I {
private:
    H h;
public:
    // 使用构造函数只调用一次带参数的构造函数构造H
    I () : h(10) {print(__FUNCTION__);}
    // 性能：没有使用初始化列表会产生两次构造
    // 进入到函数体前会先用默认构造函数构造H，进入后再次使用带参数构造函数构造H
    // I() {
    //     h = H(10);
    //     print(__FUNCTION__);
    // }
    ~I() {print(__FUNCTION__);}
};

int main () {
    // normal
    // C c; // -> A B C ~C ~B ~A

    // 初始化列表顺序
    // D d; // -> A B D ~D ~B ~A

    // 初始化列表效率
    I i; // H I ~I ~H

    // 必须：引用/const必须在初始化列表中初始化
    // A a;
    // B b;
    // E d(a, b); // A B E ~E ~B ~B ~A // const B b没有调用构造函数，原因待查

    // 必须：成员没有默认构造函数必须在初始化列表中初始化
    // G g; // F G ~G ~F

    return 0;
}