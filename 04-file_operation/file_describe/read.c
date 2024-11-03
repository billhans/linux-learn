#include <43func.h>

int main(int argc, char * argv[]) {
    // ./open file1
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    printf("fd = %d\n", fd);
    // char buf[10] = {0};
    // ssize_t ret = read(fd, buf, sizeof(buf));
    // puts(buf);
    int i;
    read(fd, &i, sizeof(i));
    printf("i = %d\n", i);
    close(fd);
}