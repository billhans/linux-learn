#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

int main() {
    unsigned short s = 0x1234;
    printf("s = %x\n", s); // 小端
    printf("htons(s) = %x\n", htons(s)); // 大端
    unsigned int i = 0x12345678;
    printf("i = %x\n", i);
    printf("htonl(i) = %x\n", htonl(i));
}