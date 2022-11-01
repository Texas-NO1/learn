#include <iostream>
#include <bits/char_traits.h>


struct T {
    static int CT;
    int x = 123;
    T() {
        std::cout << "construct T " << ++CT << std::endl;
    }
    bool operator==(const T &t) const {
        return x == t.x;
    }
};
int T::CT = 0;

int main () {
    T *x = new T[10];
    x[0].x = 123;

    int l = std::char_traits<T>::length(x);
    std::cout << l << std::endl;
    return 0;
}