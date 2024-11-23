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
// 底层用了dns协议
int main(int argc, char *argv[]) {
    // ./gethostbyname www.baidu.com
    ARGS_CHECK(argc, 2);
    struct hostent *pHost = gethostbyname(argv[1]);
    if (pHost == NULL) {
        fprintf(stderr, "gethostbyname:%s\n", strerror(h_errno));
        return -1;
    }
    printf("Host real name = %s\n", pHost->h_name);
    for (int i = 0; pHost->h_aliases[i] != NULL; ++i) {
        printf("     alias name = %s\n", pHost->h_aliases[i]);
    }
    printf("addrtype = %d\n", pHost->h_addrtype);
    printf("addrlength = %d\n", pHost->h_length);
    for (int i = 0; pHost->h_addr_list[i] != NULL; ++i) {
        char buf[1024] = {0};
        inet_ntop(pHost->h_addrtype, pHost->h_addr_list[i], buf, sizeof(buf));
        printf("     addr = %s\n", buf);
    }
}