#include <iostream>
#include <typeindex>
#include <memory>
#include <typeinfo>

struct TypeTest {} t;

int main () {
    decltype(10 + 16)* y;
    std::cout << typeid(y).name() << std::endl;
    std::cout << std::is_same<int, char>() << std::endl;
    std::cout << std::type_index(typeid(t)).name() << std::endl;
    std::cout << std::type_index(typeid(y)).hash_code() << std::endl;
    std::cout << std::__is_allocator<std::allocator<char>>() << std::endl;
    return 0;
}