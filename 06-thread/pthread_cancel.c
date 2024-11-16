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
    // printf("I am child thread, tid = %lu\n", pthread_self());
    while (1) {  // 子线程没有取消点 不会立即取消
        pthread_testcancel(); // 手动增加取消点
    }
    pthread_exit((void *)0);
}

int main() {
    printf("I am main thread, tid = %lu\n", pthread_self());
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, threadFunc, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");
    pthread_cancel(tid);
    void * retval;
    pthread_join(tid, &retval); // 如果tid是被cancel掉的，retval就是-1
    printf("child pthread return value = %ld\n", (long)retval);
}