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
    long i = (long) arg;
    sleep(1);
    printf("I am child thread, tid = %lu, i = %ld\n", pthread_self(), i);
}

int main() {
    printf("I am main thread, tid = %lu\n", pthread_self());
    pthread_t tid;
    long i = 1;
    int ret = pthread_create(&tid, NULL, threadFunc, (void *)i);
    THREAD_ERROR_CHECK(ret, "pthread_create");
    i = 2;
    printf("I am main thread, tid = %lu, i = %ld\n", pthread_self(), i);
    sleep(2);
}