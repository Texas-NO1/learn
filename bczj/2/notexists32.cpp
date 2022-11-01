#include<iostream>

void bruteForce() {
    bool all[UINT32_MAX] = {false};
    std::cout << UINT32_MAX * 4 / 1024 / 1024 / 1024 << std::endl;

    int num;
    while (std::cin >> num) {
        all[num] = true;
    }
    for (int i = 0; i < UINT32_MAX; ++i) {
        if (all[num] == false) {
            std::cout << false << std::endl;
        }
    }
}

void newFunc() {
    
}

int main () {

    return 0;
}