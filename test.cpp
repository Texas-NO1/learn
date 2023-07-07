#include <iostream>
#include <map>
#include <fstream>
#include<vector>
#include <algorithm>
#include <future>
#include <functional>
#include <chrono>

class A {
public:
   void test(std::string &res) {
      std::cout << "A test" << std::endl;
   }
   void test(std::string &res, int x) {
      std::cout << "A test and int " << std::endl;
   }
};

typedef void (A::*ATestManyParam)(std::string&, int);

class B {
public:
   A a;
   void test() {
      std::string temp = "asdf";
      //成员函数bind
      std::bind<ATestManyParam>(&A::test, &a, std::ref(temp), 123); // 方法一：指定函数类型模版参数
      std::bind((ATestManyParam)&A::test, &a, std::ref(temp), 123); // 方法二：强制类型转换
      auto f = std::bind<void (A::*)(std::string&, int)>(&A::test, &a, std::ref(temp), 123); // 方法三：指定函数类型模版参数（或强制类型转换）但不另定义函数指针类型
      f();
   }
};

int main () {
   // B b;
   // b.test();
   
   return 0;
}