#include <iostream>

class Base {
public:
    uint64_t x;
    void A() {printf("Base A\n");} // 编译时确定
    virtual void B() {printf("Base B\n");} //运行时确定 
    virtual void C() {printf("Base C %d\n", x);} //运行时确定 
};

class Extend1 : public Base {
public:
    void A() {printf("Extend1 A\n");} // 隐藏（重定义）
    void B() {printf("Extend1 B\n");} // 重写，只有父类的函数为虚函数时才算重写，子类可以省略virtual关键字
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
    std::cout << "Normal size " << sizeof(Normal) << std::endl;
    std::cout << "Base size " << sizeof(Base) << std::endl;
    std::cout << "Extend size " << sizeof(Extend1) << std::endl;


    uint64_t *x = new uint64_t[2];
    {
        Normal* test = new(x) Normal();
        test->x = 100;
        printf("front 8 bytes number Normal:%d x[0]:%d x[1]:%d\n", test->x, x[0], x[1]);
        test->x = 0;
    }
    void *base_vptr = nullptr;
    {
        Base* test = new(x) Base();
        test->x = 100;
        printf("front 8 bytes number Base:%d x[0]:%d x[1]:%d\n", test->x, x[0], x[1]); // 前8位存了一个虚函数表的指针，一个虚函数表存了一个类的所有虚函数（多继承会有多个虚函数指针）
        printf("virtual table address %p\n", x[0]);        
        test->x = 0;

        void *vptr = (void*)(x[0]);
        base_vptr = vptr;
        printf("vptr %p\n", vptr);
        //vptr就是一个指针数组，每个元素指向一个方法的地址，64位下指针长度为8字节
        uint64_t func_addr_1 = *((uint64_t*)vptr + 0); // 第一个方法地址
        uint64_t func_addr_2 = *((uint64_t*)vptr + 1); // 第二个方法地址
        printf("f1 ptr %p\n", func_addr_1);
        printf("f2 ptr %p\n", func_addr_2);
        // 用void()函数指针去解析
        void(*f1)() = (void(*)())(func_addr_1);
        void(*f2)(Base*) = (void(*)(Base*))(func_addr_2);
        (*f1)(); // 和f1()一样，相当于f1(null)
        (*f2)(test); // 和f2(test)一样，因为用到了对象的成员，所以必须传入成员指针(即调用了test->x)
        // c++的类成员方法Test(args...)，在底层的结构应该为Test(A*, args...)
    }
    {
        Extend1* test = new(x) Extend1();
        test->x = 100;
        printf("front 8 bytes number Extend1:%d x[0]:%d x[1]:%d\n", test->x, x[0], x[1]);
        printf("virtual table address %p\n", x[0]);
        test->x = 0;

        void *vptr = (void*)(x[0]);
        base_vptr = vptr;
        printf("vptr %p\n", vptr);
        //vptr就是一个指针数组，每个元素指向一个方法的地址，64位下指针长度为8字节
        uint64_t func_addr_1 = *((uint64_t*)vptr + 0); // 第一个方法地址
        uint64_t func_addr_2 = *((uint64_t*)vptr + 1); // 第二个方法地址
        printf("f1 ptr %p\n", func_addr_1);
        printf("f2 ptr %p\n", func_addr_2);
        // 用void()函数指针去解析
        void(*f1)() = (void(*)())(func_addr_1);
        void(*f2)(Base*) = (void(*)(Base*))(func_addr_2);
        (*f1)(); // 和f1()一样，相当于f1(null)
        (*f2)(test); // 和f2(test)一样，因为用到了对象的成员，所以必须传入成员指针(即调用了test->x)
        // c++的类成员方法Test(args...)，在底层的结构应该为Test(A*, args...)

        // 手动把Extend1的虚函数表指针改成Base的虚函数表指针
        printf("before change vptr %p\n", x[0]);
        test->B();
        x[0] = (uint64_t)base_vptr;
        printf("after change vptr %p\n", x[0]);
        test->B();
    }
    {
        Extend2* test = new(x) Extend2();
        test->x = 100;
        printf("front 8 bytes number Extend2:%d x[0]:%d x[1]:%d\n", test->x, x[0], x[1]);
        printf("virtual table address %p\n", x[0]);
        test->x = 0;

        void *vptr = (void*)(x[0]);
        base_vptr = vptr;
        printf("vptr %p\n", vptr);
        //vptr就是一个指针数组，每个元素指向一个方法的地址，64位下指针长度为8字节
        uint64_t func_addr_1 = *((uint64_t*)vptr + 0); // 第一个方法地址
        uint64_t func_addr_2 = *((uint64_t*)vptr + 1); // 第二个方法地址
        uint64_t func_addr_3 = *((uint64_t*)vptr + 2); // 第二个方法地址
        printf("f1 ptr %p\n", func_addr_1);
        printf("f2 ptr %p\n", func_addr_2);
        printf("f3 ptr %p\n", func_addr_3);
        // 用void()函数指针去解析
        void(*f1)() = (void(*)())(func_addr_1);
        void(*f2)(Base*) = (void(*)(Base*))(func_addr_2);
        void(*f3)() = (void(*)())(func_addr_3);
        (*f1)(); // 和f1()一样，相当于f1(null)
        (*f2)(test); // 和f2(test)一样，因为用到了对象的成员，所以必须传入成员指针(即调用了test->x)
        f3();
        // c++的类成员方法Test(args...)，在底层的结构应该为Test(A*, args...)
    }
    delete x;

    // Base *base;
    // base = new Extend1();
    // base->A(); // yes
    // base->B(); // yes
    // base->B(5); // no
    // Extend1 *t = new Extend1();
    // t->Base::B(); // yes 可以指定调用父类方法
    
    // Base *t1 = new Base();
    // Extend1 *t2 = new Extend1();
    // Base *t3 = new Extend2();
    

    // testAllFunc(t1);
    // testAllFunc(t2);
    // testAllFunc(t3);
};