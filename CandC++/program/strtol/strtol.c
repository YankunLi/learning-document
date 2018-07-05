#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "less argrement\n");
        exit(-1);
    }
    char *end;
    //transfor string to number
    //strtol strtoll strtoul strtoull
    printf("End char is : %c The num is: %ld\n", *end, strtol(argv[1], &end, 10));

    return 0;
}
