#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define ARGS_CHECK(argc, num)                 \
    {                                         \
        if (argc != num)                      \
        {                                     \
            fprintf(stderr, "args error!\n"); \
            return -1;                        \
        }                                     \
    }

int main(int argc, char *argv[]) {
    // ./ip 192.168.14.9
    ARGS_CHECK(argc, 2);
    struct in_addr addr;
    inet_aton(argv[1], &addr);
    printf("addr = %08x\n", addr.s_addr);
}

/*
~/linux-learn/07-network_programming main* ❯ ./ip 192.168.14.9
addr = 090ea8c0
*/