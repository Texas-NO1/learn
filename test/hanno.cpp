#include <iostream>

void move(int n, char x, char y, char z) {
    if (n <= 0) return;
    move(n - 1, x, z, y);
    std::cout << n << ": " << x << "->" << z << std::endl;
    move(n - 1, y, x, z);
}

int main () {
    int n = 3;
    move(n, 'A', 'B', 'C');
    return 0;
}