#include <43func.h>
int main() {
    // 栈空间
    // char buf[50] = {0};
    // char * ret = getcwd(buf, sizeof(buf));
    // ERROR_CHECK(ret, NULL, "getcwd");
    // printf("ret = %p, ret = %s\n", ret, ret);
    // printf("buf = %p, buf = %s\n", buf, buf);

    // 当不指定buf大小时，默认使用molloc分配堆空间 不free会内存泄露
    printf("cwd = %s\n", getcwd(NULL, 0));
}