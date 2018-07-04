#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int main(int argc, char argv[])
{
    FILE *fp;
    int count = 0;
    const static char *str = "hello world";
    char *filename = "./fopen.txt";
    char *temp_buf = malloc(strlen(str));

    fp = fopen(filename, "w+");
    if (!fp) {
        fprintf(stderr, "fopen file %s failed\n", filename);
        exit(-1);
    }

    printf("start write data to file %s \n", filename);
    count = fwrite(str, 1, strlen(str), fp);

    fprintf(stdout, "seek offset \n");
    fseek(fp, 0, SEEK_SET);

    fprintf(stdout, "start read data from %s \n", filename);
    count = fread(temp_buf, 1, strlen(str), fp);

    fprintf(stdout, "%s\n", temp_buf);

    return 0;
}
