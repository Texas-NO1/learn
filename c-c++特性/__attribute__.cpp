#include <iostream>

void test(int x __attribute__((__unused__))) {
    std::cout << "test" << std::endl;
}

// glic程序执行过程_start -> __libc_start_main -> exit -> _exit
__attribute__((constructor)) void test_start() {
    printf("before main\n");
    // std::cout << "before main" << std::endl; // cout会segment fault
}

int main () {
    std::cout << "main" << std::endl;

    return 0;
}