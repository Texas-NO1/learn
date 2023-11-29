#include <iostream>
#include <httplib.h>
#include "json.hpp"

using nlohmann::json;
using namespace std;
using namespace httplib;

string dump_headers(const Headers &headers) {
  string s;
  char buf[BUFSIZ];

  for (const auto &x : headers) {
    snprintf(buf, sizeof(buf), "%s: %s\n", x.first.c_str(), x.second.c_str());
    s += buf;
  }

  return s;
}

string dump_multipart_files(const MultipartFormDataMap &files) {
  string s;
  char buf[BUFSIZ];

  s += "--------------------------------\n";

  for (const auto &x : files) {
    const auto &name = x.first;
    const auto &file = x.second;

    snprintf(buf, sizeof(buf), "name: %s\n", name.c_str());
    s += buf;

    snprintf(buf, sizeof(buf), "filename: %s\n", file.filename.c_str());
    s += buf;

    snprintf(buf, sizeof(buf), "content type: %s\n", file.content_type.c_str());
    s += buf;

    snprintf(buf, sizeof(buf), "text length: %zu\n", file.content.size());
    s += buf;

    s += "----------------\n";
  }

  return s;
}

string log(const Request &req, const Response &res) {
  string s;
  char buf[BUFSIZ];

  s += "================================\n";

  snprintf(buf, sizeof(buf), "%s %s %s", req.method.c_str(),
           req.version.c_str(), req.path.c_str());
  s += buf;

  string query;
  for (auto it = req.params.begin(); it != req.params.end(); ++it) {
    const auto &x = *it;
    snprintf(buf, sizeof(buf), "%c%s=%s",
             (it == req.params.begin()) ? '?' : '&', x.first.c_str(),
             x.second.c_str());
    query += buf;
  }
  snprintf(buf, sizeof(buf), "%s\n", query.c_str());
  s += buf;

  s += dump_headers(req.headers);
  s += dump_multipart_files(req.files);

  s += "--------------------------------\n";

  snprintf(buf, sizeof(buf), "%d\n", res.status);
  s += buf;
  s += dump_headers(res.headers);

  return s;
}

int main () {

    std::string host = "0.0.0.0";
    int port = 8080;
    httplib::Server server;
    server.Get("/hi", [](const httplib::Request& req, httplib::Response& res){
        std::cout << "request get /hi " << std::endl;
        res.set_content("hello world!", "text/plain");
    });
    server.Get("/test", [](const httplib::Request& req, httplib::Response& res){
        std::cout << "request get /test " << std::endl;
        std::string name = req.get_param_value("name");
        std::string age = req.get_param_value("age");
        std::string res_csv = name + ", " + age + "\n";
        res.set_content(res_csv, "text/csv");
    });
    server.Post("/params_test", [](const httplib::Request& req, httplib::Response& res){
        std::cout << "request get /params_test " << std::endl;
        std::string name = req.get_param_value("name");
        std::string age = req.get_param_value("age");
        std::string res_csv = name + ", " + age + "\n";
        std::cout << "name " << name << ", age " << age << std::endl;
        res.set_content(res_csv, "text/plain");
    });
    server.Post("/body_test", [](const httplib::Request& req, httplib::Response& res){
        try {
            std::cout << "request get /body_test " << std::endl;
            std::cout << "req  body " << req.body << std::endl;
            json body = json::parse(req.body);
            std::string pid = body["pid"];
            std::vector<std::string> cids_parsed;
            std::string cids_string = body["cids"];
            std::string date = body["date"];
            res.set_content("ok\n", "text/plain");
        } catch (std::exception &e) {
            std::cout << "ERROR " << e.what() << std::endl;
        }
    });
    server.set_error_handler([](const Request & /*req*/, Response &res) {
        const char *fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
        char buf[BUFSIZ];
        snprintf(buf, sizeof(buf), fmt, res.status);
        res.set_content(buf, "text/html");
    });

    server.set_logger(
        [](const Request &req, const Response &res) { cout << log(req, res); });
    server.listen(host.c_str(), port);
    for (;;) {
        sleep(10);
    }
    return 0;
}