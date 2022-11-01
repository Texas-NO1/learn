#include <new>
struct Test {
    int x;
    Test() {};
    Test(int x) {};
    ~Test() {};
};

int main () {
    // Test t;
    // Test *t = new Test(10); // 1.分配空间 operator new 2.构造对象 Test()
    void *ptr = (void *)operator new(10);
    Test *t = new(ptr) Test();
    delete t; // 1.析构对象 ~Test() 2.释放空间 operator delete
    return 0;
}