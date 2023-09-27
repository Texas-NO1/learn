#include <iostream>
#include <vector>

int max = INT32_MAX / 2;
std::vector<int> prime(max + 1, 0);
int main () {
    for (int i = 2; i < max; ++i) {
        if (!prime[i]) {
            prime[++prime[0]] = i;
            // std::cout << prime[0] << ":" << i << std::endl;
        }
        for (int j = 1; j <= prime[0] && prime[j] * i < max; ++j) {
            prime[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    std::cout << prime[prime[0]] << std::endl;
    return 0;
}