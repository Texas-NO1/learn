#include <iostream>
#include <set>
#include <httplib.h>
class T {
public:
    std::string s;
    void test_this() {
        std::cout << this << std::endl;
    }
};
int main () {
    httplib::Server server;
    server.Post(R"(/pcm)", [&](const httplib::Request& req, httplib::Response& res){
        req.has_param()
    });
    return 0;
}