#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int demo(int pid, char *num, ...)
{
    va_list argp;
    int argno = 0, i;
    char *para;

    va_start(argp, num);

    printf("variable is : %s\n", argp);

//    for (i = 0; i < 5; i++)
    while (1) {
        para = va_arg(argp, char *);
        if (strcmp(para, "\n") == 0) break;
        printf("Parameter #%d addr=0x%x is: %s\n", argno, para, para);
        argno++;
    }

    va_end(argp);

    return 0;
}

int main(int argc, char *argv)
{
    demo(1, "3", "34", "rst", "ry", "yydd", "2");

    return 0;
}
