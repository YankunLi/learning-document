#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void split(char *str, const char *delim, char ***dest, int *n)
{
    char *token;
//    char **temp = *dest;
    *dest = (char**) malloc(*n * sizeof(char *));
    token = strtok(str, delim);
    int i = 0;
    while (token != NULL && --(*n)) {
        printf("split: %s\n", token);
        (*dest)[i] = token;
        i++;
        token = strtok(NULL, delim);
    }
    (*dest)[++i] = NULL;

    return;
}

int main(int argc, char *argv[])
{
    char src[] = "hello - world";
    char *delim = "-";

    char **sp;
    int n = 9;

    split(src, delim, &sp, &n);

    int i = 0;
    while (sp[i]) {
        printf("length is : %d, string is : %s\n", strlen(sp[i]), sp[i]);
        i++;
    }
    free(sp);

    return 0;
}
