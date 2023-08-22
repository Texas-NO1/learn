#include <iostream>
#include <vector>
#include <iostream>
#include "json.hpp"



int main () {
    nlohmann::json j;
    std::ofstream ou("test.json");
    ou << j;
    return 0;
}