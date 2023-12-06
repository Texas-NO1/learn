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
#include <unordered_map>
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
    Connection() : fd(-1), is_connected(false) {}
    Connection(int fd, std::string name, std::string server_name, std::string client_name) : 
    fd(fd), name(name), server_name(server_name), client_name(client_name){
        is_connected = true;
        printf("Create Connection fd %d, name %s, connect %s - %s\n", fd, name.data(), server_name.data(), client_name.data());
    }

    // 返回true，表示已读完
    // 默认情况下socket fd的read为blocking模式，只有在连接失效时才会返回0，因为一直blocking读取所以不会读取到EOF
    // 当设置read为非blocking模式时，如果读不到数据则会直接返回-1，且errno设置为EAGAIN
    bool read(std::string &receive, int read_batch = 100) { // 一次读多少字符
        std::string rec(read_batch, 0);
        // printf("s\n");
        int cnt = ::read(fd, (void *)rec.data(), rec.size()); // 4. 从连接的套接字读取数据到buff
        // printf("e\n");
        if (cnt > 0) {
            receive = rec.substr(0, cnt);
            return false;
        }
        // printf("rec %d chars, errno is %d\n", cnt, errno); // 非blocking模式下,数据读完后返回值为-1,errno设置为EAGAIN(11)
        // blocking模式下read会返回-1
        // 非blocking模式下只会在连接断开时才会返回0
        // 无论哪种情况<=0时都代表读取结束
        return true;
    }

    // 一次性读取所有内容
    std::string read() {
        std::string res;
        while (true) {
            std::string msg;
            if (read(msg)) break;
            res += msg;
        }
        return res;
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
    std::unordered_map<int, Connection> fd2conns;
    std::thread write_thread; // 另起一个线程写数据
    bool is_running;

    std::string genNewConnName() {
        return "connection-" + std::to_string(fd2conns.size());
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
        is_running = true;
    }

    void setnonblocking(int fd) {
        int flags = fcntl(fd, F_GETFL);
        assert(flags >= 0);
        flags |= O_NONBLOCK;
        int res = fcntl(fd, F_SETFL, flags);
        assert(res >= 0);
    }

    // 使用epoll，仅用一个线程维持所有连接
    void start() {
        int epollfd = epoll_create1(0);
        assert(epollfd >= 0);
        printf("create a epoll fd %d to control all connection\n", epollfd);
        struct epoll_event ev;
        ev.events = EPOLLIN; // EPOLLIN监听进事件(文件可读时)
        ev.data.fd = fd;
        // 服务端套接字也设置为nonblocking（假设对这个fd读写的话）
        setnonblocking(fd);
        int status = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev); // EPOLL_CTL_ADD添加一个fd(socket)到epollfd管理
        assert(status >= 0);
        int events_batch = 100; // 设一次最大获取100个事件
        std::vector<struct epoll_event> events(events_batch);
        while (is_running) {
            int nfds = epoll_wait(epollfd, events.data(), events_batch, -1); // -1表示block住直到有事件发生
            assert(nfds >= 0);
            for (int i = 0; i < nfds; ++i) {
                // printf("fd %d has new event %d\n", events[i].data.fd, events[i].events);
                // 事件为server的fd，表示有新连接
                if (events[i].data.fd == fd) {
                    int new_fd = accept(fd, nullptr, nullptr);
                    assert(new_fd >= 0);
                    struct sockaddr_in addr;
                    socklen_t size = 0;
                    getsockname(new_fd, (sockaddr *)&addr, &size);
                    std::string client_addr = inet_ntoa(addr.sin_addr);
                    client_addr += ":" + std::to_string(addr.sin_port);
                    fd2conns[new_fd] = std::move(Connection(new_fd, genNewConnName(), name, client_addr));
                    // 连接不可阻塞，否则会一直卡在读取某个连接上
                    setnonblocking(new_fd);
                    struct epoll_event new_ev;
                    // 可读事件 + 边缘触发(EdgeTrigger) + 错误事件
                    // 边缘触发表示，一次事件仅发送一次通知，下次新事件再来时才会重新发送通知
                    // 所以边缘触发时一定要将所有数据循环读完，因为一次收到的数据可能会大于的buff size，需要不断循环获取完所有数据再退出
                    // EPOLLERR事件会默认被监听，不需要额外配置
                    new_ev.events = EPOLLIN | EPOLLET | EPOLLHUP | EPOLLRDHUP;
                    new_ev.data.fd = new_fd;
                    status = epoll_ctl(epollfd, EPOLL_CTL_ADD, new_fd, &new_ev);
                    assert(status >= 0);
                } else {
                    // 事件为connection的fd，表示连接有新数据或者连接有问题
                    int event_fd = events[i].data.fd;
                    // 使用&判断events中是否有对应事件
                    if (events[i].events & EPOLLIN) {
                        // 连接有数据进来，读取并输出
                        std::string msg = fd2conns[event_fd].read();
                        if (!msg.empty()) printf("\n%s\n", msg.data());
                    } else {
                        printf("fd %d unexcept event %d\n", event_fd,  events[i].events);
                    }
                }
                if (events[i].events & (EPOLLHUP | EPOLLRDHUP)) {
                    int event_fd = events[i].data.fd;
                    printf("connection fd %d closed, remove it\n", event_fd);
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, event_fd, nullptr);
                    fd2conns[event_fd].close();
                    fd2conns.erase(event_fd);
                }
            }
        }
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
                    for (auto &fd2conn : fd2conns) {
                        printf("%d : %s ", fd2conn.first, fd2conn.second.getName().data());
                        if (fd2conn.second.isClosed()) printf("(closed)"); // TODO delete closed conn
                        else support_conns.insert(fd2conn.first);
                        printf("\n");
                    }
                    printf("You can choose one client to reply: ");
                    int reply_idx;
                    std::cin >> reply_idx;
                    if (!support_conns.count(reply_idx)) {
                        printf("client choosed has been closed or not exsists\n");
                        continue;
                    }
                    choose_conn = &(fd2conns[reply_idx]);
                    printf("reply: ");
                    std::string reply_str;
                    std::cin >> reply_str;
                    choose_conn->write(reply_str);
                }
            }
        });
    }

    ~Server() {
        is_running = false;
        printf("Destroy Server, close fd %d\n", fd);
        int status = close(fd);
        assert(status >= 0);
        for (auto &fd2conn : fd2conns) {
            fd2conn.second.close();
        }
    }
};

int main () {
    signal(SIGINT, signalHandler);
    signal(SIGFPE, signalHandler);
    signal(SIGSEGV, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGKILL, signalHandler); // 不能捕捉
    Server server("qxai-server-"+ std::to_string(getpid()), "0.0.0.0", 12345);
    server.continueWriting();
    server.start();
    return 0;
}