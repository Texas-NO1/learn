#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <cassert>
#include <iostream>

#define SERVER_PORT 12345

int main () {
    int pid = getpid();
    printf("current pid is %d\n", pid);
    std::string location = "/proc/" + std::to_string(pid) + "/fd";
    printf("socket location may in %s\n", location.data());

    int fd = socket(AF_INET, SOCK_STREAM, 0); // 1. 创建套接字
    printf("server fd is %d\n", fd);
    assert(fd >= 0);
    int status = 0;
    int reuseaddr = 1;
    status = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr)); // 2. 配置套接字
    assert(status >= 0);
    struct sockaddr_in server_addr;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // 任意ip都可访问
    status = bind(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)); // 3. 绑定套接字到端口
    assert(status >= 0);
    status = listen(fd, 5); // 4. 监听套接字
    assert(status >= 0);
    // 目前一个connection仅支持一次对话，后续提升
    // 1. 一个connection支持多次对话
    // 2. connection设置超时时间，超时套接字自动失活
    // 3. buff没有'\0'后缀，需要判断长度并加上
    // 4. read和write放入队列由单独线程执行
    // 5. 测试指定s_addr（可能是防火墙）
    while (true) {
        struct sockaddr_in conn_addr;
        socklen_t conn_size = sizeof(conn_addr);
        // conn_size是否为传出参数？
        int conn_fd = accept(fd, (sockaddr *)&conn_addr, &conn_size); // 5. 接收套接字连接，返回的是新套接字
        printf("connection fd is %d conn_size %d\n", conn_fd, conn_size);
        assert(conn_fd >= 0);
        char buff[100];
        status = read(conn_fd, buff, sizeof(buff)); // 6. 从连接的套接字读取数据到buff
        printf("%s\n", buff);
        assert(status >= 0);
        std::string res;
        std::cin >> res;
        status = write(conn_fd, res.data(), res.size()); // 7. 写数据到连接的套接字（client接收）
        assert(status >= 0);
        status = close(conn_fd); // 8.关闭连接的套接字
        assert(status >= 0);
    }
    status = close(fd); // 9.关闭服务端套接字
    assert(status >= 0);
    return 0;
}