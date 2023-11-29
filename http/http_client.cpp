#include <iostream>
#include <httplib.h>
#include "json.hpp"

int main () {
    // 先运行http_server，再运行http_client
    httplib::Client client("localhost", 8080);
    client.set_keep_alive(true); // 保持连接
    {
        httplib::Result res = client.Get("/hi");
        std::cout << "req = /hi, res = " <<  res.value().body << std::endl;
    }
    {
        httplib::Result res = client.Get("/test?name=TexasNO1&age=18");
        std::cout << "req = /test?name=TexasNO1&age=18, res = " <<  res.value().body << std::endl;
    }
    {
        httplib::Result res = client.Post("/body_test");
        std::cout << "req = /body_test, no body, res =" << res.value().body << std::endl;
    }
    {
        nlohmann::json j;
        j["pid"] = "12345";
        j["cids"] = "12345,23456,34567";
        j["date"] = "20231122";
        std::string body = j.dump();
        httplib::Result res = client.Post("/body_test", body, "text/plain");
        // httplib::Result res = client.Post("/body_test", body, "application/json");
        std::cout << "req = /body_test, no body, res =" << res.value().body << std::endl;
    }
    return 0;
}