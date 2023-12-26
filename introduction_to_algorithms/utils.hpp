#include <iostream>
#include <string>

template<class T>
void output(const T &vec) {
    for (auto &v : vec) std::cout << v << ",";
    std::cout << std::endl;
}