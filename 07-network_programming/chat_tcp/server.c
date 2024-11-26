#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define ARGS_CHECK(argc, num)                 \
    {                                         \
        if (argc != num)                      \
        {                                     \
            fprintf(stderr, "args error!\n"); \
            return -1;                        \
        }                                     \
    }

#define ERROR_CHECK(ret, num, msg) \
    {                              \
        if (ret == num)            \
        {                          \
            perror(msg);           \
            return -1;             \
        }                          \
    }

int main(int argc, char *argv[]) {
    // ./server 192.168.217.129 1234
    ARGS_CHECK(argc, 3);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");
    int optval = 1;
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)); // 让服务器无视TIME_WAIT
    ERROR_CHECK(ret, -1, "setsockopt");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "bind");
    ret = listen(sockfd, 10);
    ERROR_CHECK(ret, -1, "listen");
    int netfd = accept(sockfd, NULL, NULL);
    ERROR_CHECK(netfd, -1, "accept");

    fd_set rdset;
    char buf[4096] = {0};
    while (1) {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(netfd, &rdset);
        select(netfd+1, &rdset, NULL, NULL, NULL);
        if (FD_ISSET(STDIN_FILENO, &rdset)) { // 如果标准输入来的数据
            bzero(buf, sizeof(buf));
            ret = read(STDIN_FILENO, buf, sizeof(buf));
            if (ret == 0) {
                send(netfd, "nishigehaoren", 13, 0);
                break;
            }
            send(netfd, buf, strlen(buf), 0);
        }
        if (FD_ISSET(netfd, &rdset)) {
            bzero(buf, sizeof(buf));
            ret = recv(netfd, buf, sizeof(buf), 0);
            if (ret == 0) {
                puts("chat is end!");
                break;
            }
            puts(buf);
        }
    }
    close(sockfd);
    close(netfd);
}
/*
netstat -an|grep 1234 可以看见1234端口进入TIME_WAIT状态
*/