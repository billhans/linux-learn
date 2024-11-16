#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM 10000000

#define THREAD_ERROR_CHECK(ret, msg) \
    {                                \
        if (ret != 0)                \
        {                            \
            perror(msg);             \
            return -1;               \
        }                            \
    }
// 由于两个线程同时访问和修改count 且加操作不是原子操作 导致数据竞争
void *threadFunc(void *arg) {
    int *pCount = (int *)arg;
    for (int i = 0; i < NUM; ++i) {
        ++*pCount;
    }
}

int main() {
    pthread_t tid;
    int count = 0;
    int ret = pthread_create(&tid, NULL, threadFunc, (void *)&count);
    THREAD_ERROR_CHECK(ret, "pthread_create");
    for (int i = 0; i < NUM; ++i) {
        ++count;
    }
    pthread_join(tid, NULL);
    printf("count = %d\n", count);

    return 0;
}