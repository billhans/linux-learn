#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *threadFunc(void *arg) {
    printf("I am child thread, tid = %lu\n", pthread_self());
    return NULL; // 多线程并发执行
}

int main() {
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, threadFunc, NULL);
    printf("I am main thread, tid = %lu\n", pthread_self());
    sleep(1); // 如果这里取消sleep 结果只会打印主线程 主线程终止 整个线程也就终止了
    return 0;
}