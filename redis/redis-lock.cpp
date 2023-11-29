#include <iostream>
#include <vector>
#include <thread>
#include <unistd.h>
#include <sw/redis++/redis++.h>
// g++ -std=c++17 redis/redis-lock.cpp -lredis++ -lhiredis -pthread
// 同时运行两个进程模拟分布式锁

using namespace sw::redis;

void release() {
    auto redis = Redis("tcp://redis:6379");
    std::string key = "uniqe-lock";
    redis.del(key);
}

void test(std::string id) {
    auto redis = Redis("tcp://redis:6379");
    std::string key = "uniqe-lock";
    bool get_lock = false;
    while (!get_lock) {
        // get_lock = redis.setnx(key, "true"); // without ttl
        get_lock = redis.set(key, "true", std::chrono::milliseconds(1*60*60*1000), UpdateType::NOT_EXIST);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::cout << id << " get lock, do something...\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));

    auto res1 = redis.del(key);
    if (res1) {
        std::cout << id << " release lock\n";
    } else {
        std::cout << id << " lock not exists\n";
    }
}

int main () {
    release();
    std::string pid = std::to_string(getpid());
    std::vector<std::thread> ts;
    for (int i = 0; i < 10; ++i) {
        ts.push_back(std::thread(test, pid + "-" + std::to_string(i)));
    }
    for (auto &t : ts) t.join();

    // auto res = redis.setnx("lock", "true");
    // std::cout << "setnx res " << res << std::endl;
    // auto res1 = redis.get("lock");
    // std::cout << "get res " << res1.value() << std::endl;
    // auto res2 = redis.del("lock");
    // std::cout << "del res " << res2 << std::endl;
    return 0;
}