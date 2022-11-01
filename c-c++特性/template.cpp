#include <iostream>
#include <type_traits>

template<typename T>
struct Type {
    int y;
};

template<typename T, typename L = int>
struct T1 {
    T x;
    L y;
    void output() {
        std::cout << "T L output : " << x << y << std::endl;
    }
    void show() {
        std::cout << "show" << std::endl;
    }
};


template<typename T>
struct T1<Type<T>>{
    void output() {
        std::cout << "T<Type<T>> output : " << std::endl;
    }
};

template<>
struct T1<Type<int>>{
    Type<int> x;
    void output() {
        std::cout << "T output : " << x.y << std::endl;
    }
};

struct Base {
    void test() {
        std::cout << "BASE" << std::endl;
    }
};

template<typename T>
struct Extend : Base {
};

template<>
struct Extend<int> {
};

template<bool, class Tp>
struct Test {
    static void out() {
        std::cout << "normal Test" << std::endl;
    }
};

template<class Tp>
struct Test<true, Tp> {
    static void out() {
        std::cout << "normal Test true" << std::endl;
    }
};

template<int>
struct TTT {
    
};

template<int MAX_SIZE = 100>
struct TTT1 {
    
};





// 偏特化和特化后的类已经是完全独立的类，可以有不同的成员方法、成员变量，可以想象为是两个名字相同但内容不同的类，但一般情况下为了扩展和泛用成员也会保持相同

int main () {
    T1<Type<int>> t;
    t.output();

    Extend<char> x;
    x.test();
    Extend<int> y; // Extend<int>没有继承Base
    // y.test();

    Test<false, int>::out();
    Test<true, int>::out();
    return 0;
}