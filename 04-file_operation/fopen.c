#include <43func.h>

int main(int argc, char *argv[]) {
    ARGS_CHECK(argc, 2);
    // FILE *fp = fopen(argv[1], "a");
    // ERROR_CHECK(fp, NULL, "fopen");
    // fwrite("howareyou", 1, 9, fp);
    FILE *fp = fopen(argv[1], "a+");
    ERROR_CHECK(fp, NULL, "fopen");
    char buf[10] = {0};
    fread(buf, 1, 9, fp);
    fwrite("howareyou", 1, 9, fp);
    fclose(fp);
}