#include <iostream>

class Base1 {
public:
    void A() {printf("Base1 A\n");} // 编译时确定
    virtual void B() {printf("Base1 B\n");} //运行时确定 
    virtual void C() {printf("Base1 C\n");} //运行时确定 
};

class Base2 {
public:
    void A() {printf("Base2 A\n");} // 编译时确定
    virtual void B() {printf("Base2 B\n");} //运行时确定 
    virtual void C() {printf("Base2 C\n");} //运行时确定 
};

class Extend : public Base1, Base2 {
public:
    void B() {printf("Extend B\n");} //运行时确定 
};



int main () {

    printf("Base1 = %d\n", sizeof(Base1));
    printf("Base2 = %d\n", sizeof(Base2));
    printf("Extend = %d\n", sizeof(Extend));

    Base1 b1;
    Base2 b2;

    Extend e;

    uint64_t vtptrb1 = *((uint64_t*)(&b1) + 0);
    uint64_t vtptrb2 = *((uint64_t*)(&b2) + 0);
    uint64_t vtptre1 = *((uint64_t*)(&e) + 0);
    uint64_t vtptre2 = *((uint64_t*)(&e) + 1);

    printf("Base1 vtptr = %p\n", vtptrb1);
    printf("Base2 vtptr = %p\n", vtptrb2);
    printf("Extend vtptr 1 = %p\n", vtptre1);
    printf("Extend vtptr 2 = %p\n", vtptre2);

    for (int i = 0; i < 2; ++i) {
        printf("Base 1 vtable func %d = %p\n", i, *((uint64_t*)vtptrb1 + i));
    }
    for (int i = 0; i < 2; ++i) {
        printf("Base 2 vtable func %d = %p\n", i, *((uint64_t*)vtptrb2 + i));
    }
    for (int i = 0; i < 2; ++i) {
        printf("Extend 1 vtable func %d = %p\n", i, *((uint64_t*)vtptre1 + i));
    }
    for (int i = 0; i < 2; ++i) {
        printf("Extend 2 vtable func %d = %p\n", i, *((uint64_t*)vtptre2 + i));
    }

    void (*f1)() = (void(*)())(*((uint64_t*)vtptre1 + 0));
    void (*f2)() = (void(*)())(*((uint64_t*)vtptre2 + 0));
    f1();
    f2();

    printf("f1 %p\n", f1);
    printf("f2 %p\n", f2);

    // e.B();
    return 0;
}