#include <iostream>

struct A {
    uint32_t x;
    uint32_t y;
};

struct AA {
    uint64_t z;
};

struct B : public A {
    uint64_t z;
};

struct C {
    virtual void test() {
        std::cout << "This is C" << std::endl;
    }
};

struct D : public C {
    void test() {
        std::cout << "This is D" << std::endl;
    }
};

int main () {
    // static_cast强制类型转换，类似于c的(T)t;
    {
        char x = 'a';
        auto res = static_cast<uint64_t>(x);
        // 常用于void*与其他类型指针的转换
        void *temp = static_cast<void*>(&x);
        std::cout << res << std::endl;
        // static_cast<B>(A()); // 报错，父类类型不能强制转换为子类类型
        // auto temp = static_cast<uint64_t>(a); // 报错，static_cast不能强制类型转换不相关的类型
        A *a = new A();
        a->x = 1;
        a->y = 2;
        B *b = static_cast<B*>(a); // 父类指针可以强制转换为子类指针
        std::cout << b->x << " " << b->y << std::endl;
        // dynamic_cast<B*>(a); // 报错，dynamic_cast必须包含多态类型
    }
    // dynamic_cast多态场景下的类型转换，必须为多态类型
    {
        C *c = new C();
        c->test();
        C *cc = new D();
        cc->test();

        // D *d = cc; // 报错C*类型不能赋值给D*类型
        D *dd = dynamic_cast<D*>(cc); // 使用dynamic_cast则可以赋值，前提是cc确实是D类型，否则调用dd方法会报错
        dd->test();

        // D *d = dynamic_cast<D*>(c); // c为new C()，编译不报错
        // d->test(); // 但运行出错，因为是运行时绑定的
    }
    // const_cast解除const修饰，还有volatile
    {
        int a = 10;
        const int &b = a;
        // b = 15; // 报错因为b为const修饰的不可修改的左值
        int &c = const_cast<int&>(b); // const_cast必须是const的引用或指针类型
        c = 15;
        std::cout << b << std::endl; // b转换为15
    }
    // reinterpret_cast位的简单重新解释获取
    {
        A *a = new A();
        a->x = 1;
        a->y = 2;
        // 0x00000001 0x00000002
        // 内存中存储的bit数据为0x0000000100000002
        // 但由于小端模式，解析时由于0x00000001在内存低位所以是低位字节，0x00000002在内存高位所以在高位字节
        // 用uint64_t解析时获得的值为0x0000000200000001
        AA *aa = reinterpret_cast<AA*>(a);
        std::cout << aa->z << ", 0x" << std::hex << aa->z << std::endl;
        uint64_t address = reinterpret_cast<uint64_t>(a);
        std::cout << a << " " << std::hex << address << std::endl;
    }

    return 0;
}