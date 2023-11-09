#include <iostream>
#include "thread_pool.hpp"
#include <sstream>

std::mutex mtx;
void output(std::stringstream &ss) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << ss.str();
}

int main () {
    ThreadPool pool(4);
    std::vector<std::future<int>> fs;
    for (int i = 0; i < 10; ++i) {
        fs.push_back(pool.commit([id=i](){std::this_thread::sleep_for(std::chrono::seconds(1));std::stringstream ss; ss << "current execute " << id << std::endl; output(ss); return id;}));
    }
    for (auto &f : fs) {
        std::stringstream ss;
        ss << "main thread get " << f.get() << std::endl;
        output(ss);
    }
    return 0;
}