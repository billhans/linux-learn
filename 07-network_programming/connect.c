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
// 先socket指定服务端地址 调用connect发第一次握手
int main(int argc, char *argv[]) {
    // ./connect 192.168.14.9 1234
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");
    printf("sockfd = %d\n", sockfd);
    struct sockaddr_in addr; // 创建时用sockaddr_in
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    int ret = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "connect");
    close(sockfd);
}
/*
bhhh@ubuntu:~/linux-learn/07-network_programming$ sudo tcpdump -i lo port 1234
tcpdump: verbose output suppressed, use -v[v]... for full protocol decode
listening on lo, link-type EN10MB (Ethernet), snapshot length 262144 bytes
15:08:42.792396 IP ubuntu.48004 > ubuntu.1234: Flags [S], seq 362900678, win 65495, options [mss 65495,sackOK,TS val 2686327860 ecr 0,nop,wscale 7], length 0
15:08:42.792401 IP ubuntu.1234 > ubuntu.48004: Flags [R.], seq 0, ack 362900679, win 0, length 0
*/