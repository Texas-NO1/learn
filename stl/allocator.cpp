#include <iostream>
#include <string>
#include <vector>

struct Test {
    int *id;
    static int TOTAL;
    Test() {
        id = new int(++TOTAL);
        std::cout << "construct " << *id << std::endl;
    }
    Test(const Test& t) {
        id = new int(*t.id);
        std::cout << "copy construct " << *id << std::endl;
    }
    ~Test() {
        std::cout << "destroy " << *id << std::endl;
        delete id;
    }
};
int Test::TOTAL = 0;

int main (){
    Test t;
    std::basic_string<Test> s;
    for (int i = 0; i < 5; ++i) {
        s.push_back(t);
    }
    return 0;
}