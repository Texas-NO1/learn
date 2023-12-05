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
    
    int fd = socket(AF_INET, SOCK_STREAM, 0); // 1. 创建套接字TCP/IP协议
    int status = 0;
    assert(fd >= 0);
    struct sockaddr_in server_addr;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // 任意ip都可访问，访问本地ip
    status = connect(fd, (struct sockaddr*)&server_addr, sizeof(server_addr)); // 2. 使用套接字连接server
    assert(status >= 0);
    std::string input;
    std::cin >> input;
    status = write(fd, input.data(), input.size()); // 3. 写数据到套接字
    assert(status >= 0);
    char buff[100];
    int cnt = read(fd, buff, sizeof(buff) - 1); // 4. 从连接的套接字读取数据到buff
    assert(cnt >= 0);
    buff[cnt] = '\0';
    printf("read %d chars: %s\n", cnt, buff);
    status = close(fd); // 5. 关闭客户端套接字
    assert(status >= 0);
    return 0;
}