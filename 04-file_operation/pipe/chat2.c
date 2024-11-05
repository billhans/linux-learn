#include <43func.h>

int main(int argc, char *argv[]) {
    // ./chat2 1.pipe 2.pipe
    ARGS_CHECK(argc, 3);
    int fdw = open(argv[1], O_WRONLY);
    int fdr = open(argv[2], O_RDONLY);
    puts("pipe open");
    
}