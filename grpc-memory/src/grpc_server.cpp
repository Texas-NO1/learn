#include <iostream>
#include <unistd.h>
#include "src/generated/template.pb.h"
#include "src/generated/template.grpc.pb.h"

#include <jemalloc/jemalloc.h>

#include <grpc/grpc.h>
#include <grpcpp/grpcpp.h>

struct TEST {
    int x;
    char y;
    double ttl;
    std::string s;
    std::unordered_map<std::string, std::string> res;
};

class GreeterServiceImpl final : public greeter::Greeter::Service {
    grpc::Status SayHello(grpc::ServerContext* context, const greeter::HelloRequest* request, greeter::HelloReply* reply) override {
        try {
            std::string s;
            for (int i = 0; i < 100000; ++i) {
                s += std::to_string(rand());
            }
            reply->set_message(s);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        return grpc::Status::OK;
    }
    
    grpc::Status Dump(grpc::ServerContext* context, const greeter::Empty* request, greeter::Empty* response) {
        try {
            mallctl("prof.dump", NULL, NULL, NULL, 0);
            std::cout << "dump over" << std::endl;
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        return grpc::Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:20200");
    GreeterServiceImpl service;

    grpc::ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main () {
    RunServer();
    return 0;
}