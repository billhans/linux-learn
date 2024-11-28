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
#include <sys/epoll.h>

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
    struct sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = inet_addr(argv[1]);
    serAddr.sin_port = htons(atoi(argv[2]));
    int ret = 0;
    int reuse = 1; // 表示允许地址重用
    ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    ERROR_CHECK(ret, -1, "setsockopt");

    ret = bind(sockfd, (struct sockaddr *)&serAddr, sizeof(serAddr));
    ERROR_CHECK(ret, -1, "bind");
    ret = listen(sockfd, 10);
    ERROR_CHECK(ret, -1, "listen");
    
    // newfd代表的是客户端的TCP连接
    int newfd = accept(sockfd, NULL, NULL);
    ERROR_CHECK(newfd, -1, "accept");
    char buf[64] = {0};
    int epfd = epoll_create(1);
    ERROR_CHECK(epfd, -1, "epoll_create");
    struct epoll_event event, evs[2];
    memset(&event, 0, sizeof(event));
    // 把关心的描述符和对应的时间填到结构体
    event.data.fd = STDIN_FILENO;
    event.events = EPOLLIN;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl");
    event.data.fd = newfd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, newfd, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl");

    int readNum = 0;
    while (1) {
        readNum = epoll_wait(epfd, evs, 2, -1);
        for (int i = 0; i < readNum; i ++) {
            if (evs[i].data.fd == STDIN_FILENO) {
                memset(buf, 0, sizeof(buf));
                send(newfd, buf, strlen(buf)-1, 0);
            }
            else if (evs[i].data.fd == newfd) {
                memset(buf, 0, sizeof(buf));
                ret = recv(newfd, buf, sizeof(buf), 0);
                // 对端断开的时候 newfd一直可读
                // recv读数据的返回值是0
                if (0 == ret) {
                    printf("byebye\n");
                    close(sockfd);
                    close(newfd);
                    return 0;
                }
                printf("buf = %s\n", buf);
            }
        }
    }
    close(newfd);
    close(sockfd);
    return 0;
}