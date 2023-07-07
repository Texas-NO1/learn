#include <iostream>
#include <string>



template<typename T>
class Template {
public:
    static void test() {
        T::output();
    }
};

int main() {
    std::vector<int> s;
    s.find(1, 0);

    return 0;
}