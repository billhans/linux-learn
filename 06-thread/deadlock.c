#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
    // pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALZER; // 静态初始化
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL); // 如果第二个参数是NULL，表示以默认形式初始化锁
    pthread_mutex_lock(&mutex);
    puts("lock one time!");
    pthread_mutex_lock(&mutex);
    puts("lock two time!");
    pthread_mutex_destroy(&mutex);
}