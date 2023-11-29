#include <iostream>
#include "src/generated/template.pb.h"
#include "src/generated/template.grpc.pb.h"
#include "src/include/thread_pool.hpp"

#include <grpc/grpc.h>
#include <grpc++/grpc++.h>
#include <grpcpp/grpcpp.h>
#include <unistd.h>

void hello() {
    grpc::ClientContext context;
    greeter::HelloRequest req;
    greeter::HelloReply res;
    std::string s;
    for (int i = 0; i < 100000; ++i) {
        s += std::to_string(rand());
    }
    req.set_name(s);
    auto channel = grpc::CreateChannel("localhost:20200", grpc::InsecureChannelCredentials());
    auto stub = greeter::Greeter::NewStub(channel);
    
    auto stats = stub->SayHello(&context, req, &res);
    static int count = 0;
    if (stats.ok()) {
        std::cout << "hello over " << ++count << std::endl;
        std::cout << res.message() << std::endl;
    } else {
        std::cout << "error message " << stats.error_message() << std::endl;
    }
}

void dump() {
    grpc::ClientContext context;
    greeter::Empty req;
    greeter::Empty res;
    auto channel = grpc::CreateChannel("localhost:20200", grpc::InsecureChannelCredentials());
    auto stub = greeter::Greeter::NewStub(channel);
    
    auto stats = stub->Dump(&context, req, &res);
    if (stats.ok()) {
        std::cout << "dump over" << std::endl;
    } else {
        std::cout << "error message " << stats.error_message() << std::endl;
    }
}

// begin 12660

int main () {
    ThreadPool pool(30);
    dump();
    std::vector<std::future<void>> fs;
    // sleep(30);
    for (int i = 0; i < 10000; ++i) {
        fs.push_back(pool.commit(&hello));
    }
    for (auto &f : fs) {
        f.get();
    }
    dump();
    return 0;
}