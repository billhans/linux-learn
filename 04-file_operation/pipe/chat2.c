#include <43func.h>

int main(int argc, char *argv[]) {
    // ./chat2 1.pipe 2.pipe
    ARGS_CHECK(argc, 3);
    int fdw = open(argv[1], O_WRONLY);
    int fdr = open(argv[2], O_RDONLY);
    printf("I am chat2\n");
    char buf[128] = {0};
    while (1) {
        memset(buf, 0, sizeof(buf));
        read(fdr, buf, sizeof(buf));
        printf("buf = %s\n", buf);
        memset(buf, 0, sizeof(buf));
        read(STDIN_FILENO, buf, sizeof(buf));
        write(fdw, buf, strlen(buf) - 1);
    }
    return 0;
}