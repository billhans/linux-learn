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
#include <fcntl.h>

#define ERROR_CHECK(ret, num, msg) \
    {                              \
        if (ret == num)            \
        {                          \
            perror(msg);           \
            return -1;             \
        }                          \
    }

int setNonblock(int fd)
{
    int ret = 0, status = 0; // 获取描述符的当前的状态
    status = fcntl(fd, F_GETFL);
    status |= O_NONBLOCK;
    ret = fcntl(fd, F_SETFL, status);
    ERROR_CHECK(ret, -1, "fcntl");
    return 0;
}
int main()
{
    char buf[64] = {0};
    setNonblock(STDIN_FILENO); // 设置为非阻塞的方式后
    // 如果有数据，会读数据出来
    // 如果没有数据，不会阻塞，会返回-1
    int ret = read(STDIN_FILENO, buf, sizeof(buf));
    printf("ret=%d,buf=%s\n", ret, buf);
    ERROR_CHECK(ret, -1, "read");
    return 0;
}