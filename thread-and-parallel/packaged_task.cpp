#include <iostream>
#include <future>
#include <thread>
#include <functional>
#include <vector>

int test(int x, int y) {
    return x + y;
}

// emplace_back需要调用构造函数，lambda表达式转std::function时需要复制参数值，但packaged_task的拷贝构造不可调用
int error_func() {
    std::vector<std::function<void()>> tasks;
    std::packaged_task<decltype(test(2, 11))()> task(std::bind(test, 2, 11));
    auto future = task.get_future();
    auto f = [new_task=std::move(task)]() mutable {new_task();};
    // tasks.emplace_back(f);  // 编译失败
    tasks.front()();
    std::cout << future.get() << std::endl;
}

 // 使用shared_ptr包装packaged_task，拷贝构造指针而不是packaged_task
int right_func() {
    std::vector<std::function<void()>> tasks;
    auto task = std::make_shared<std::packaged_task<decltype(test(2, 11))()>>(std::bind(test, 2, 11));
    auto future = task->get_future();
    tasks.emplace_back([task]() mutable {(*task)();});
    tasks.front()();
    std::cout << "res = " << future.get() << std::endl;
}

int main()
{
    right_func();
}