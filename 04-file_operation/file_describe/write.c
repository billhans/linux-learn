#include <43func.h>

int main(int argc, char * argv[]) {
    // ./open file1
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    printf("fd = %d\n", fd);
    // char buf[10] = "hello"; // 这里如果是字符串，就是文本文件
    // write(fd, buf, strlen(buf));
    int i = 10000000;
    write(fd, &i, sizeof(i));
    close(fd);
}