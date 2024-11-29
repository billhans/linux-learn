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
    //1 创建文件对象
    int epfd = epoll_create(1);
    ERROR_CHECK(epfd, -1, "epoll_create");
    printf("epfd = %d\n", epfd); // epfd = 3
    //2 设置监听

    //3 陷入阻塞 直到任一监听就绪
    
    //4 遍历就绪事件队列 处理事件
        close(epfd);
}