#include <iostream>
#include <algorithm>

int main () {
    int n = 10000, k = 100;
    int vec[n];
    for (int i = 0; i < n; ++i) {
        vec[i] = i;
    }
    for (int i = 0; i < k; ++i) {
        std::swap(vec[i], vec[rand() % (n - i) + i]);
        std::cout << vec[i] << std::endl;
    }
    return 0;
}