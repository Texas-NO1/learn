#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <cassert>
#include <iostream>
#include <signal.h>
#include <arpa/inet.h>
#include "thread_pool.hpp"

bool running;
void signalHandler(int signal) {
    std::cout << "get signal " << signal << ", so exit, pid " << getpid() << std::endl;
    if (running == false) {
        std::cout << "force exit" << std::endl;
        exit(signal);
    }
    running = false;
}

class Connection {
private:
    int fd; // socket文件描述符
    std::string name; // 给连接一个名字
    std::string server_name; // 连接的服务端名字
    std::string client_name; // 连接的客户端名字
public:
    Connection(int fd, std::string name, std::string server_name, std::string client_name) : 
    fd(fd), name(name), server_name(server_name), client_name(client_name){
        printf("Create Connection name %s, connect %s - %s\n", name.data(), server_name.data(), client_name.data());
    }

    std::string read(int read_batch = 100) { // 一次读多少字符
        std::string receive(read_batch, '\0');
        int status = ::read(fd, (void *)receive.data(), receive.size()); // 4. 从连接的套接字读取数据到buff
        assert(status >= 0);
        return receive;
    }

    void write(std::string input) {
        input = server_name + ": " + input;
        int status = ::write(fd, input.data(), input.size()); // 3. 写数据到套接字
        assert(status >= 0);
    }

    void close() {
        printf("Close Connection, fd %d\n", fd);
        int status = ::close(fd);
        assert(status >= 0);
    }

    ~Connection() {}
};

class Server {
private:
    int fd; // socket文件描述符
    int pid; // 进程pid
    std::string name; // 给server一个名字
    std::vector<Connection> conns;

    std::string genNewConnName() {
        return "connection-" + std::to_string(conns.size());
    }
public:
    Server(std::string name, std::string host, int port, int max_conn = 1) {
        this->name = name;
        pid = getpid();
        printf("Create new Server name %s, pid %d\n", name.data(), pid);
        fd = socket(AF_INET, SOCK_STREAM, 0); // 1. 创建套接字TCP/IP协议
        assert(fd >= 0);
        std::string location = "/proc/" + std::to_string(pid) + "/fd/";
        printf("init server socket location may in %s, fd is %d\n", location.data(), fd);
        int status = 0;
        int reuseaddr = 1;
        status = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr)); // 2. 配置套接字
        assert(status >= 0);
        struct sockaddr_in server_addr;
        server_addr.sin_port = htons(port);
        server_addr.sin_family = AF_INET;
        // server_addr.sin_addr.s_addr = INADDR_ANY; // 用预设的一些ip赋值
        // https://www.ibm.com/docs/en/zos/2.5.0?topic=lf-inet-aton-convert-internet-address-format-from-text-binary
        status = inet_aton(host.data(), &server_addr.sin_addr); // 用传入的ip赋值，地址字符串转in_addr,返回非0表示地址正常
        assert(status != 0);
        status = bind(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)); // 3. 绑定套接字到端口
        assert(status >= 0);
        status = listen(fd, max_conn); // 4. 监听套接字
        assert(status >= 0);
    }

    // 等待连接
    void waitting() {
        struct sockaddr_in addr;
        socklen_t size = 0;
        int new_fd = accept(fd, (struct sockaddr*)&addr, &size);
        assert(new_fd >= 0);
        std::string client_addr = inet_ntoa(addr.sin_addr);
        client_addr += ":" + std::to_string(addr.sin_port);
        printf("get a new connection from %s address size %d\n", client_addr.data(), size);
        conns.push_back(Connection(new_fd, genNewConnName(), name, client_addr));
    }

    void backgroup() {
        
    }

    ~Server() {
        printf("Destroy Server, close fd %d\n", fd);
        int status = close(fd);
        assert(status >= 0);
        for (auto &conn : conns) {
            conn.close();
        }
    }
};

int main () {
    signal(SIGINT, signalHandler);
    signal(SIGFPE, signalHandler);
    signal(SIGSEGV, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGKILL, signalHandler); // 不能捕捉
    running = true;
    Server server("qxai02", "0.0.0.0", 12345);
    while (running) {
        server.waitting();
    }
    return 0;
}