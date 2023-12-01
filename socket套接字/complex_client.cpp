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
#include <thread>
#include <vector>

bool running;
void signalHandler(int signal) {
    std::cout << "get signal " << signal << ", so exit, pid " << getpid() << std::endl;
    if (running == false) {
        std::cout << "force exit" << std::endl;
        exit(signal);
    }
    running = false;
}

class Client {
private:
    int fd; // socket文件描述符
    int pid; // 进程pid
    std::string name; // 给client一个名字
    bool is_connected; // 保持连接
    std::thread reading_thread; // 持续读
public:
    Client(std::string name, std::string host, int port) {
        this->name = name;
        pid = getpid();
        printf("Create new Client name %s, pid %d\n", name.data(), pid);
        fd = socket(AF_INET, SOCK_STREAM, 0); // 1. 创建套接字TCP/IP协议
        assert(fd >= 0);
        std::string location = "/proc/" + std::to_string(pid) + "/fd/";
        printf("init client socket location may in %s, fd is %d\n", location.data(), fd);
        int status = 0;
        struct sockaddr_in server_addr;
        server_addr.sin_port = htons(port);
        server_addr.sin_family = AF_INET;
        // server_addr.sin_addr.s_addr = INADDR_ANY; // 用预设的一些ip赋值
        // https://www.ibm.com/docs/en/zos/2.5.0?topic=lf-inet-aton-convert-internet-address-format-from-text-binary
        status = inet_aton(host.data(), &server_addr.sin_addr); // 用传入的ip赋值，地址字符串转in_addr,返回非0表示地址正常
        assert(status != 0);
        status = connect(fd, (struct sockaddr*)&server_addr, sizeof(server_addr)); // 2. 使用套接字连接server
        assert(status >= 0);
        is_connected = true;
    }

    bool read(std::string &receive, int read_batch = 100) { // 一次读多少字符
        std::string rec(read_batch, 0);
        // printf("s\n");
        int cnt = ::read(fd, (void *)rec.data(), rec.size()); // 4. 从连接的套接字读取数据到buff
        // printf("e\n");
        assert(cnt >= 0);
        receive = rec.substr(0, cnt);
        // printf("rec %d chars\n", cnt);
        return cnt == 0;
    }

    void continueReading() {
        reading_thread = std::thread([this] {
            while (this->is_connected) {
                // printf("reading\n");
                std::string msg;
                if (this->read(msg)) close(); // connaction close since socket closed
                if (!msg.empty()) 
                    printf("\n%s\n", msg.data());
            }
        });
    }

    void close() {
        is_connected = false;
        printf("Destroy client, close fd %d\n", fd);
        int status = ::close(fd);
        assert(status >= 0);
    }

    void write(std::string input) {
        input = name + ": " + input;
        int status = ::write(fd, input.data(), input.size()); // 3. 写数据到套接字
        // printf("write res %d\n", status);
        assert(status >= 0);
    }

    ~Client() {}
};

int main () {
    signal(SIGINT, signalHandler);
    signal(SIGFPE, signalHandler);
    signal(SIGSEGV, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGKILL, signalHandler); // 不能捕捉
    running = true;
    Client client("qxai-client-" + std::to_string(getpid()), "0.0.0.0", 12345);
    // Client client("qxai-client-" + std::to_string(getpid()), "47.100.220.86", 12345);
    client.continueReading();
    while (running) {
        printf("Say: ");
        std::string input;
        std::cin >> input;
        client.write(input);
    }
    return 0;
}