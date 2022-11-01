#include <iostream>
#include <bits/basic_string.h>


template<typename T>
class Type {
private:
    T a;
    void test(T &a, const T &b) {
        a = b;
    }
public:
    Type() {
        T b;
        test(a, b);
    }
};

int main () { 
    Type<Type<int>> x;
    return 0;
}