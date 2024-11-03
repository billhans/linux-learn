#include <43func.h>

int main(int argc, char * argv[]) {
    // ./open file1
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDONLY);
    ERROR_CHECK(fd, -1, "open");
    printf("fd = %d\n", fd);
    close(fd);
}