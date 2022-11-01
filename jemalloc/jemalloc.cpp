#include <iostream>
#include <unistd.h>
#include <jemalloc/jemalloc.h>
#include <vector>

// std::vector<std::string> vec;

void test() {
    for (int i = 0; i < 1024; ++i) {
        void *ptr = malloc(1024);
        // free(ptr);
    }
    // for (int i = 0; i < 32768; ++i) {
    //     vec.push_back(std::string());
    // }
}

int main () {
    std::cout << getpid() << std::endl;
    mallctl("prof.dump", NULL, NULL, NULL, 0);
    test();
    mallctl("prof.dump", NULL, NULL, NULL, 0);
    return 0;
}