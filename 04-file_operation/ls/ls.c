#include <43func.h>

int main(int argc, char *argv[]) {
    // ./ls dir
    ARGS_CHECK(argc, 2);
    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp, NULL, "opendir");
    struct dirent * pdirent;
    pdirent = readdir(dirp);

    while ((pdirent = readdir(dirp)) != NULL) {
        printf("inode = %ld, reclen = %d, type = %d, name = %s\n",
                pdirent->d_ino, pdirent->d_reclen, pdirent->d_type, pdirent->d_name);
    }
    closedir(dirp);
}
/*
~/linux-learn/04-file_operation/ls main* ❯ ./ls .
inode = 140626, reclen = 24, type = 8, name = ls.c
inode = 141096, reclen = 32, type = 8, name = Makefile
inode = 140621, reclen = 24, type = 4, name = .
inode = 142137, reclen = 24, type = 8, name = ls
*/