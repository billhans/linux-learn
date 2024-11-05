#include <43func.h>

int main(int argc, char *argv[]) {
    ARGS_CHECK(argc, 2);
    int fdw = open(argv[1], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open");
    printf("fdw = %d\n", fdw);
    char buf[128] = "helloworld";
    write(fdw, buf, strlen(buf));
    printf("buf = %s\n", buf);
    close(fdw);
    return 0;
}