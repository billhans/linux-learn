#include <43func.h>

int main(int argc, char *argv[]) {
    // ./chat1 1.pipe 2.pipe
    ARGS_CHECK(argc, 3);
    int fdr = open(argv[1], O_RDONLY);
    int fdw = open(argv[2], O_WRONLY);
    printf("I am chat1\n");
    char buf[128] = {0};
    fd_set rdset; // 申请一个监听集合
    while (1) {
        FD_ZERO(&rdset); // 清空
        // 添加 标准输入和fdr 两个导致阻塞的文件描述符
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(fdr, &rdset);

        struct timeval timeout;
        timeout.tv_sec = 2;
        timeout.tv_usec = 500000;

        int sret = select(fdr + 1, &rdset, NULL, NULL, &timeout); // 陷入等待状态
        if (sret == 0) {
            printf("time out!\n");
            continue;
        }
        
        if (FD_ISSET(fdr, &rdset)) { // 如果管道有数据 则从管道进行读取
            puts("msg from pipe");
            memset(buf, 0, sizeof(buf));
            int ret = read(fdr, buf, sizeof(buf));
            if (ret == 0) {
                printf("end!\n");
                break;
            }
            printf("buf = %s\n", buf);
        }
        if (FD_ISSET(STDIN_FILENO, &rdset)) {
            puts("msg from stdin");
            memset(buf, 0, sizeof(buf));
            int ret = read(STDIN_FILENO, buf, sizeof(buf));
            if (ret == 0) {
                write(fdw, "baibai", 6);
                break;
            }
            write(fdw, buf, strlen(buf) - 1);
        }
    }
    return 0;
}