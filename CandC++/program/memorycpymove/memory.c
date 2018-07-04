#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    const static char *str = "hello world";
    char buf[100];

    memcpy(buf, str, strlen(str) + 1);
    printf("buffed is : %s\n", buf);

    memmove(buf + 6, buf, 5);
    fprintf(stdout, "modified buffed data is : %s\n", buf);

    return 0;
}
