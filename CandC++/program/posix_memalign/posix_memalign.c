#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//valgrind memcheck for posix_memalign
int main(int argc, char *argv)
{
    void *buf[128];
    int i = 0, ret = 0;
    long addr;

    for (i = 0; i < 128; i++) {
        ret = posix_memalign(&buf[i], 512, 1024);
        if (ret) {

        }
        memcpy(&addr, &buf[i], sizeof(long));
        printf("%d %d\n", sizeof(buf[i]), sizeof(long));
        printf("index %d : address: %d  %d align: %d\n", i, buf[i], addr, (int) addr % 512);
        sleep(0.5);
    }

    for (i = 0; i < 128; i++) {
        free(buf[i]);
    }

    return 0;
}
