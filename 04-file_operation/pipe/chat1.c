#include <43func.h>

int main(int argc, char *argv[]) {
    // ./chat1 1.pipe 2.pipe
    ARGS_CHECK(argc, 3);
    int fdr = open(argv[1], O_RDONLY);
    int fdw = open(argv[2], O_WRONLY);
    printf("I am chat1\n");
    char buf[128] = {0};
    while (1) {
        memset(buf, 0, sizeof(buf));
        read(STDIN_FILENO, buf, sizeof(buf));
        write(fdw, buf, strlen(buf) - 1);
        memset(buf, 0, sizeof(buf));
        read(fdr, buf, sizeof(buf));
        printf("buf = %s\n", buf);
    }
    return 0;
}