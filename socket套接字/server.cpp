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
#include <unordered_set>
#include <vector>
#include <thread>
#include <sys/epoll.h> // TODO多路复用（当前策略为一个客户端连接一个线程监听，连接过多时不可用）

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
    int is_connected; // 是否连接
    std::string name; // 给连接一个名字
    std::string server_name; // 连接的服务端名字
    std::string client_name; // 连接的客户端名字
public:
    Connection(int fd, std::string name, std::string server_name, std::string client_name) : 
    fd(fd), name(name), server_name(server_name), client_name(client_name){
        is_connected = true;
        printf("Create Connection fd %d, name %s, connect %s - %s\n", fd, name.data(), server_name.data(), client_name.data());
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
        printf("(Client %s Connection %s) start reading\n",
            client_name.data(),
            name.data());
        while (is_connected) {
            // printf("reading\n");
            std::string msg;
            if (read(msg)) close(); // connaction close since socket closed
            if (!msg.empty()) printf("\n%s\n", msg.data());
            printf("type r to reply");
        }
    }

    void write(std::string input) {
        input = server_name + ": " + input;
        int status = ::write(fd, input.data(), input.size()); // 3. 写数据到套接字
        assert(status >= 0);
    }

    void close() {
        if (is_connected) {
            is_connected = false;
            printf("Close Connection, fd %d\n", fd);
            int status = ::close(fd);
            assert(status >= 0);
        }
    }

    bool isClosed() {
        return !is_connected;
    }

    std::string getName() {
        return name;
    }

    ~Connection() {}
};

class Server {
private:
    int fd; // socket文件描述符
    int pid; // 进程pid
    std::string name; // 给server一个名字
    std::vector<Connection> conns;
    std::vector<std::thread> listen_threads;
    std::thread write_thread; // 另起一个线程写数据

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
        int new_fd = accept(fd, nullptr, nullptr); // 这里addr可能获取不到，直接从fd中getsockname
        struct sockaddr_in addr;
        socklen_t size = 0;
        getsockname(new_fd, (sockaddr *)&addr, &size);
        assert(new_fd >= 0);
        std::string client_addr = inet_ntoa(addr.sin_addr);
        client_addr += ":" + std::to_string(addr.sin_port);
        // printf("get a new connection from %s address size %d\n", client_addr.data(), size);
        conns.push_back(std::move(Connection(new_fd, genNewConnName(), name, client_addr)));
        listen_threads.push_back(std::thread(&Connection::continueReading, conns.back()));
    }

    void continueWriting() {
        write_thread = std::thread([this]{
            while (true) {
                Connection *choose_conn = nullptr;
                char choice;
                std::cin >> choice;
                std::string op;
                switch (choice) {
                    case 'r':
                        op = "reply";
                        break;
                    default:
                        printf("support keys: r\n");
                        break;
                }
                if (op == "reply") {
                    printf("\nConnection List: \n");
                    std::unordered_set<int> support_conns;
                    for (int i = 0; i < this->conns.size(); ++i) {
                        printf("%d : %s ", i, this->conns[i].getName().data());
                        if (this->conns[i].isClosed()) printf("(closed)"); // TODO delete closed conn
                        else support_conns.insert(i);
                        printf("\n");
                    }
                    printf("You can choose one client to reply: ");
                    int reply_idx;
                    std::cin >> reply_idx;
                    if (!support_conns.count(reply_idx)) {
                        printf("client choosed has been closed or not exsists\n");
                        continue;
                    }
                    choose_conn = &(this->conns[reply_idx]);
                    printf("reply: ");
                    std::string reply_str;
                    std::cin >> reply_str;
                    choose_conn->write(reply_str);
                }
            }
        });
    }

    ~Server() {
        printf("Destroy Server, close fd %d\n", fd);
        int status = close(fd);
        assert(status >= 0);
        for (int i = 0; i < conns.size(); ++i) {
            conns[i].close();
            if (listen_threads[i].joinable())
                listen_threads[i].join();
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
    Server server("qxai-server-"+ std::to_string(getpid()), "0.0.0.0", 12345);
    server.continueWriting();
    while (running) {
        server.waitting();
    }
    return 0;
}