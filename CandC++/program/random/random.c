#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv)
{
    int i = 0;

    srandom(time(NULL));

    for (i = 0; i < 10; i++) {
        printf("random %d is %d\n", i, random());
    }

    return 0;
}
