#include <iostream>
#include <vector>

// enum name，作用域为全局作用域
enum Color {BLUE,RED=5,GREEN};
// enum class name，作用域为类作用域，需要用class::方式获取
enum class ColorClass {RED=7,GREEN=10};

int main () {
    Color color = RED; // 等价于::Color color = ::RED;
    ColorClass new_color = ColorClass::RED; // 不能直接使用GREEN
    return 0;
}