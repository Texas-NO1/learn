#include <iostream>
#include <string>
#include <vector>

class T {
public:
    T() {
        str = "";
        x = -1;
        printf("construct T\n");
    };
    T& operator=(const T &t) {
        x = t.x;
        str = t.str;
        printf("copy T\n");
        return *this;
    }
private:
    long long x;
    std::string str;
};


int main () {
    std::basic_string<T> str;
    return 0;
}