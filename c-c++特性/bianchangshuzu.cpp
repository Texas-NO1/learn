#include <iostream>
#include <vector>

// struct ErrorStruct {
//     char x[]; // 不能变长数组开头
// };

// struct ErrorStruct {
//     int y;
//     char x[]; // 变长数组后面不能有成员
//     int z;
// };

struct Test {
    int y;
    char x[];
};

int main () {
    std::cout << sizeof(Test) << std::endl; // 变长数组不占用size
    return 0;
}