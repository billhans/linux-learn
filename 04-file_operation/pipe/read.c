#include <43func.h>

int main(int argc, char *argv[]) {
    ARGS_CHECK(argc, 2);
    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open");
    printf("fdr = %d\n", fdr);
    char buf[128] = {0};
    read(fdr, buf, sizeof(buf));
    printf("buf = %s\n", buf);
    close(fdr);
    return 0;
}

/*
当一个进程打开（open）了管道一端的时候
如果对端未被打开，进程处于阻塞状态
直到对端被另一个进程打开为止
*/