#include <iostream>
#include "inline.h"

// non-inline方法可以在一个文件内声明，另一个文件内定义
void InlineTest::nonInlineTest() {
    std::cout << "no inline" << std::endl;
}
