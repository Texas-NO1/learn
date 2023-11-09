#include <iostream>
#include <vector>
#include <fstream>
#include "json.hpp"
#include <map>
#include <unordered_map>
#include <ctime>
#include <iomanip>

// using nlohmann::json;
int main () {
    // nlohmann::json j = std::map<std::string,std::string>();
    // json j(json::value_t::object);
    // // j["ss"] = 1;
    // // j["xxx"] = "sdaf";
    // std::cout << j.empty() << " " << j.size() << std::endl;
    // std::ofstream ou("test.json");
    // ou << j;
    // std::vector<int> v;
    // v.push_back(1);
    // std::cout << v.size() << std::endl;
    // v.pop_back();
    // std::cout << v.size() << std::endl;
    // std::cout << std::hash<int>()(10) << std::endl;
    // float x = 122343.23434;
    // float y = 0;
    // printf("%.10f %.10f\n", y, std::modf(x, &y));
    // std::cout << std::hash<float>()(x);

    // std::cout << "\n" << std::hash<int>()(-10);
    // std::cout << "\n" << std::hash<long long>()(-10);
    // uint64_t len = 5;
    // std::cout << std::hex << ~(size_t)0x7 << std::endl;
    // const size_t len_aligned = len & ~(size_t)0x7;
    // std::cout << len_aligned << std::endl;

    // int x = 1;
    // printf("%p\n", &x);
    // int y = 2;
    // printf("%p\n", &y);
    // char z = 'x';
    // printf("%p\n", &z);
    // int i = 2;
    // printf("%p\n", &i);
    std::string s = "";
    for (char x : s) std::cout << int(x) << std::endl;
    std::cout << s.size() << std::endl;
    std::cout << s << std::endl;
    return 0;
}