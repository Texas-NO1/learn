#include <iostream>
#include <vector>
#include <thread>
#include <unistd.h>
#include <sw/redis++/redis++.h>
// g++ -std=c++17 redis/redis-lock.cpp -lredis++ -lhiredis -pthread
// 同时运行两个进程模拟乐观锁
// redis trancaction vs pipeline
// pipeline是提高RTT（网络传输时间），即一批命令一次性打包发送，网络io降低
// trancaction是开启事务，可以选择是否使用pipeline完成事务，具有原子性，但不具有回滚操作（回滚某一次执行完成的事务）

using namespace sw::redis;

void test(std::string id) {
    auto redis = Redis("tcp://redis:6379");
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000)); // do something
    std::cout << id << " get lock, do something...\n";
    std::string key = "CAS";
    redis.watch(key);
    int val = 0;
    auto res = redis.get(key);
    if (res.has_value()) val = std::stoi(res.value());
    std::cout << id << " begin " << key << "=" << val << std::endl;
    std::string new_val = std::to_string(val + 1);
    // redis.incr(key); // 事务执行前中断
    // std::cout << "before pipeline, change to " << redis.get(key).value() << std::endl;
    std::cout << id << " do some thing..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 5000)); // do something
    auto res_after_sleep = redis.get(key);
    int val_after_sleep = 0;
    if (res_after_sleep.has_value()) val_after_sleep = std::stoi(res_after_sleep.value());
    std::cout << id << " after sleep " << key << "=" << val << std::endl;
    try {
        auto resvec = redis.transaction(true, false)
                .set(key, new_val)
                .get(key)
                .exec();
        std::cout << id << " in pipeline: set " << key << " res " << resvec.get<bool>(0)  << std::endl;
        std::cout << id << " in pipeline: get " << key << "=" << resvec.get<std::string>(1)  << std::endl;
        std::cout << "is same value " << val << "?" << val_after_sleep << " = " << (val_after_sleep == val) << std::endl;
    } catch (std::exception &e) {
        std::cout << "get error " << e.what() << ", is same value " << val << "?" << val_after_sleep << " = " << (val_after_sleep == val) << std::endl;
    }
}

int main () {
    std::string pid = std::to_string(getpid());
    std::vector<std::thread> ts;
    for (int i = 0; i < 10; ++i) {
        ts.push_back(std::thread(test, pid + "-" + std::to_string(i)));
    }
    for (auto &t : ts) t.join();
    return 0;
}