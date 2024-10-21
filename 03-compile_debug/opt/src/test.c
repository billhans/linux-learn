//#define DEBUG

#include <stdio.h>
#include "test.h"

int main() {
#ifdef DEBUG
    puts("DEBUG exists!");
#endif

    printf("add(3, 4) = %d\n", add(3, 4));
    return 0;
}

int add(int lhs, int rhs) {
    return lhs + rhs;
}