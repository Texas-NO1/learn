#include <iostream>

int main () {
    std::string cid = "chasdfasdfasdf";
    if (cid.substr(0, 2) == "ch") {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}