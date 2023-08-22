#include <iostream>
#include <vector>
#include <fstream>
#include "json.hpp"
#include <map>

using nlohmann::json;
int main () {
    // nlohmann::json j = std::map<std::string,std::string>();
    json j(json::value_t::object);
    // j["ss"] = 1;
    // j["xxx"] = "sdaf";
    std::cout << j.empty() << " " << j.size() << std::endl;
    std::ofstream ou("test.json");
    ou << j;
    return 0;
}