#include <bits/allocator.h>
#include <iostream>
#include <ext/algorithm>
#include <string>

// 16byte
struct T1 {
    double y;
    int x;
    static int COUNT;
    T1() {
        x = -1;
        y = -1;
        printf("T1 construct %d\n", ++COUNT);
    }
};
int T1::COUNT = 0;

struct T2 {
    char x;
};

int main () {
    std::basic_string<T1> ts;
    for (int i = 0; i < 10; ++i) {
        T1 t;
        ts.push_back(t);
    }
    std::cout << ts[9].x << ts[9].y << std::endl;
    return 0;
}