#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *threadFunc(void *arg) {
    printf("I am child thread, tid = %lu\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, threadFunc, NULL);
    printf("I am main thread, tid = %lu\n", pthread_self());
    sleep(1);
    return 0;
}