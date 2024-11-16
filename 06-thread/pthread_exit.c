#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define THREAD_ERROR_CHECK(ret, msg) \
    {                                \
        if (ret != 0)                \
        {                            \
            perror(msg);             \
            return -1;               \
        }                            \
    }

void *threadFunc(void *arg) {
    printf("I am child thread, tid = %lu\n", pthread_self());
    return (void *)666;
}

int main() {
    printf("I am main thread, tid = %lu\n", pthread_self());
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, threadFunc, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");
    long retval; // 申请了8个字节
    pthread_join(tid, (void **)&retval);
    // 主线程要拿&retval所指的内存空间，存储子线程的返回值
    printf("retval = %ld\n", retval);
}
/*
~/linux-learn/06-thread main* ❯ ./pthread_exit
I am main thread, tid = 139680315250496
I am child thread, tid = 139680315246144
retval = 666
*/