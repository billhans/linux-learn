#include <43func.h>

int main(int argc, char *argv[]) {
    // .cp src dst 源文件拷贝到目标文件
    ARGS_CHECK(argc, 3);
    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open fdr");
    int fdw = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    ERROR_CHECK(fdw, -1, "open fdw");
    char buf[4096] = {0}; // buf越大越好 可以减少状态切换的次数
    while (1) {
        memset(buf, 0, sizeof(buf));
        ssize_t ret = read(fdr, buf, sizeof(buf));
        if (ret == 0) {
            break;
        }
        write(fdw, buf, ret); // 第三个参数是ret 表示读多少写多少
    }
    close(fdr);
    close(fdw);
}
/*
~/linux-learn/04-file_operation/cp main* ❯ ./cp cp.c test
~/linux-learn/04-file_operation/cp main* ❯ ls
cp*  cp.c  Makefile  test
~/linux-learn/04-file_operation/cp main* ❯ ll
.rwxr-xr-x 16k bhhh bhhh  3 Nov 23:09 cp*
.rw-r--r-- 613 bhhh bhhh  3 Nov 23:08 cp.c
.rw-r--r--  85 bhhh bhhh  3 Nov 22:58 Makefile
.rw-r--r-- 613 bhhh bhhh  3 Nov 23:09 test
~/linux-learn/04-file_operation/cp main* ❯ 
*/