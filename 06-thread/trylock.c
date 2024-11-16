#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define THREAD_ERROR_CHECK(ret, msg) \
    {                                \
        if (ret != 0)                \
        {                            \
            perror(msg);             \
            return -1;               \
        }                            \
    }

int main() {
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL); // 如果第二个参数是NULL，表示以默认形式初始化锁
    int ret = pthread_mutex_trylock(&mutex);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_trylock 1");
    ret = pthread_mutex_trylock(&mutex);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_trylock 2");
    pthread_mutex_destroy(&mutex);
}