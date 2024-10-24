#include <43func.h>

int main(int argc, char *argv[]) {
    ARGS_CHECK(argc, 2);
    FILE *fp = fopen(argv[1], "r");
    ERROR_CHECK(fp, NULL, "fopen");
    fclose(fp);
}