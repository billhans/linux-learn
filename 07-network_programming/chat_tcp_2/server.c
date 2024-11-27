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
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sfd, -1, "socket");
    struct sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = inet_addr(argv[1]);
    serAddr.sin_port = htons(atoi(argv[2]));
    int ret = bind(sfd, (struct sockaddr *)&serAddr, sizeof(serAddr));
    ERROR_CHECK(ret, -1, "bind");
    ret = listen(sfd, 10);
    ERROR_CHECK(ret, -1, "listen");
    int newFd = 0;
    char buf[64] = {0};
    fd_set rdset; // 记录的是需要监听的文件描述符的集合
    fd_set needMonitorSet;
    FD_ZERO(&rdset);
    FD_ZERO(&needMonitorSet);
    FD_SET(STDIN_FILENO, &needMonitorSet);
    FD_SET(sfd, &needMonitorSet);
    while (1)
    {
        memcpy(&rdset, &needMonitorSet, sizeof(fd_set));
        ret = select(10, &rdset, NULL, NULL, NULL);
        ERROR_CHECK(ret, -1, "readyNum"); // select的rdset是一个传入传出参数，select成功返回的时候
        // rdset里保存的是就绪的描述符
        printf("select return\n");
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            memset(buf, 0, sizeof(buf));
            read(STDIN_FILENO, buf, sizeof(buf));
            send(newFd, buf, strlen(buf) - 1, 0);
        }   
        else if (FD_ISSET(newFd, &rdset))
        {
            memset(buf, 0, sizeof(buf));
            ret = recv(newFd, buf, sizeof(buf), 0); // 对端断开的时候，newFd一直可读
            // recv读数据的返回值是0
            if(0 == ret){
            printf("byebye\n");
            close(newFd);
            FD_CLR(newFd, &needMonitorSet);
            continue;
            }
        printf("buf=%s\n", buf);
        }
        else if (FD_ISSET(sfd, &rdset))
        {
            // sfd可读，表示客户端连接我们
            // newFd代表的是跟客户端的TCP连接
            printf("accpet\n");
            struct sockaddr_in cliAddr;
            memset(&cliAddr, 0, sizeof(cliAddr));
            socklen_t sockLen = sizeof(cliAddr);
            printf("sockLen=%d\n", sockLen);
            /* socklen_t sockLen = 0; */
            newFd = accept(sfd, (struct sockaddr *)&cliAddr, &sockLen);
            ERROR_CHECK(newFd, -1, "accept");
            FD_SET(newFd, &needMonitorSet);
            printf("sockLen=%d\n", sockLen);
            printf("newFd=%d\n", newFd);
            printf("addr=%s,port=%d\n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
        }
    }
    close(newFd);
    close(sfd);
    return 0;
}
/*
netstat -an|grep 1234 可以看见1234端口进入TIME_WAIT状态
*/