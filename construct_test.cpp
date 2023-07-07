
class A {
public: 
   A(int x) {}; 
};

class B : public A {
    using A::A;
};

int main () {
    B b = 10;
    return 0;
}