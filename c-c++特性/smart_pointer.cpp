#include <iostream>
#include <memory>
class T {
public:
    T() {printf("%s\n",__FUNCTION__);};
    ~T() {printf("%s\n",__FUNCTION__);};
};

int main () {
    // 一个原始指针只能由一个指针指针管理
    T *t = new T();
    // shared_ptr模版参数就是目标类型，而不是目标指针类型
    std::shared_ptr<T> sp(t); // 或 std::shared_ptr<T> sp = std::shared_ptr<T>(t);
    std::cout << sp.use_count() << std::endl;


    // 16字节:最底层为两个指针，指向对象的指针，指向计数器的指针。
    // shared_ptr的计数器也是new出来的，而计数器对象大小为24字节
    // shared_ptr本身是线程安全的（依据c++版本多线程环境下就是线程安全的）
    // 这里指的线程安全指的是基于一个shared_ptr，创建多个shared_ptr或销毁部分shared_ptrptr
    // 在并发环境下所有shared_ptr的计数器是能准确进行+1-1操作的。
    // 而对于shared_ptr并不保证指向的原始指针的线程安全
    std::cout << "share_ptr size: " << sizeof(sp) << std::endl;
    // 计数器对象大小24字节，除去继承关系最底层包含4个成员：
    // 1.指向对象的指针,8字节
    // 2.计数器_M_use_count(int类型),4字节
    // 3.计数器_M_weak_count(int类型),4字节
    // 4.同步类型_Mutex_base结构包含enum类型成员,4字节
    // 内存对齐后大小为24
    std::cout << "ptr counter size: " << sizeof(std::_Sp_counted_ptr<T*, std::_S_atomic>) << std::endl;
    // 两个int计数器+enum类型，字节对齐16字节
    std::cout << "counter base size: " << sizeof(std::_Sp_counted_base<std::_S_atomic>) << std::endl;

    // 多个shared_ptr指向同一个智能指针，每个shared_ptr计数都会+1
    std::shared_ptr<T> sp1 = sp;
    std::cout << sp.use_count() << " " << sp1.use_count() << std::endl;

    // weak_ptr不会影响use_count
    std::weak_ptr<T> wp = sp;
    std::cout << wp.use_count() << std::endl;
    std::cout << "weak_ptr size: " << sizeof(std::weak_ptr<T>) << std::endl;

    T *nt = new T();
    // std::unique_ptr<T> up = std::unique_ptr<T>(sp); // 错误: shared_ptr不能赋值给unique_ptr
    std::unique_ptr<T> up(nt);
    // 8字节：unique_ptr仅包含原始指针自身
    std::cout << "unique_ptr size: " << sizeof(std::unique_ptr<T>) << std::endl;

    // 错误：两个shared_ptr构造指向同一个指针就会造成double free问题
    // std::shared_ptr<T> new_sp = std::shared_ptr<T>(t);

    // 错误：weak_ptr无法通过原始指针构建，只能通过share_ptr或unique_ptr创建
    // std::weak_ptr<T> wp = std::weak_ptr<T>(t);

    return 0;
}