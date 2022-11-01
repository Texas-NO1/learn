#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>

struct Point {
    float x;
    float y;
};

struct T {
    Point point;
    uint64_t timestamp;
    std::string floor;
    std::vector<std::string> channels;
};

struct NewT {
    Point point; //8 
    uint64_t timestamp;//8
    short *channels;//8
    int floor; // 2
    int ch_size;// 2
};

struct TestShort {
    int y;
    std::vector<int> x;
};

enum Cloor {a, b};
struct TestEnum {
    Cloor c;
    int *p;
    int *l;
    int *r;
};

struct TEST {
    int x;
    std::string y;
    char xxx[1024]; 
    TEST(){

    }
    TEST(const TEST &t) {
        y = t.y;
    }
};

int main () {
    std::vector<TEST> vec;
    for (int i = 0; i < 10000000; ++i) {
        int x = rand();
    }
    for (int i = 0; i < 100; ++i) {
        TEST t;
        t.x = 1000;
        vec.push_back(t);
        std::cout << vec[0].x << " cap " << vec.capacity() << " xxx " << vec[0].xxx << std::endl;
    }
    // std::cout << sizeof(std::set<std::string>) << std::endl;

    // std::shared_ptr<std::string> s;
    // if (s) {
    //     std::cout << *s << std::endl;
    // }

    // std::weak_ptr<std::string> s2;
    // {
    //     std::unordered_map<std::string, std::shared_ptr<std::string>> test;
    //     {
    //         std::shared_ptr<std::string> s = std::shared_ptr<std::string>(new std::string("123"));
    //         test["123"] = s;
    //         std::cout << s.use_count() << std::endl;
    //     } 
    //     s2 = test["123"];
    // }
    // std::cout << s2.use_count() << std::endl;
    // std::shared_ptr<std::string> s2shared = s2.lock();
    // if (s2shared) {
    //     std::cout << *s2shared << std::endl;
    // }

    // std::cout << sizeof(TestEnum) << std::endl;

    // std::vector<int> temp;
    // temp.push_back(1);
    // temp.push_back(2);

    // std::vector<int> vec;
    // vec.insert(vec.end(), temp.begin(), temp.end());

    // std::cout << sizeof(T) << std::endl;
    // std::cout << sizeof(NewT) << std::endl;

    // std::string s = "ch28e73a89-ee98-409e-ae9d-0e5976e753a8_1640422800000_417";
    // std::cout << sizeof(s) << std::endl;
    // std::cout << s.size() << std::endl;
    // std::cout << sizeof(std::set<T>) << std::endl;
    // std::cout << sizeof(std::set<std::string>) << std::endl;
    // std::cout << sizeof(std::map<std::string, std::string>) << std::endl;
    // std::cout << sizeof(std::unordered_set<std::string>) << std::endl;
    // std::cout << sizeof(std::unordered_map<std::string, std::string>) << std::endl;
    // std::cout << sizeof(float) << std::endl;

    // std::cout << sizeof(T) << std::endl;
    // std::cout << sizeof(std::string) << std::endl;
    // std::cout << sizeof(std::vector<std::string>) << std::endl;
    // std::cout << sizeof(std::_Rb_tree_node<T>) << std::endl;
    // std::cout << sizeof(TestEnum) << std::endl;
    // std::cout << sizeof(std::_Rb_tree_node_base) << std::endl;
    // std::_Rb_tree_node_base x;
    // std::cout << sizeof(x._M_color) << std::endl;
    // std::cout << sizeof(x._M_left) << std::endl;
    // std::cout << sizeof(x._M_right) << std::endl;
    // std::cout << sizeof(x._M_parent) << std::endl;
    return 0;
}