#include "createLib.h" // 都要包含头文件
// 使用动态库 g++ useLib.cpp createLib.h -L. -lcreateLib -o a.out （默认使用动态库，且运行时需要在系统目录下存在/添加当前路径）
// 使用静态库 g++ -static useLib.cpp createLib.h -L. -lcreateLib -o a.out （-static优先使用静态库，直接将库内容装到可执行文件中，运行时不需要库）
int main() {
    output();
    return 0;
}