#include <iostream>
#include "inline.h"

int main () {
    InlineTest t;
    t.nonInlineTest();
    t.inlineTest();
    return 0;
}