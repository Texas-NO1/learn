#include <iostream>


void g() noexcept(true) {
    std::cout << "g" << std::endl;
}

void g(int x) {
    std::cout << "g x" << std::endl;
} 

int main () {


    g();

    return 0;
}