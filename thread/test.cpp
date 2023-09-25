#include <iostream>
#include <vector>
#include <thread>
#include <map>

int main () {
    try {
        std::vector<int> v;
        std::cout << *v.begin() << std::endl;
    } catch (std::exception &e) {
        std::cout << "get exception " << e.what() << std::endl;
    }
    std::cout << "over" << std::endl;
    return 0;
}