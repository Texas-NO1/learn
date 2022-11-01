#include <iostream>

class Base1 {
public:
    virtual void A() {};
};

class Base2 {
public:
    virtual void B() {};
};

class Base3 {
public:
    virtual void C() {};
};

class Extend : public Base1, public Base2, public Base3 {
    // void A() {};
};

int main () {
    Extend *e = new Extend();
    std::cout << sizeof(Extend) << std::endl;
    return 0;
}