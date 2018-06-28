#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    const static char *str_ptr = "where is the char";
    const static char ch = 'r';
    const char * chr_ptr = NULL;

    chr_ptr = strrchr(str_ptr, ch);
    if (chr_ptr) {
        printf("string is : %s\n", str_ptr);
        printf("The index of char %c is %d \n", ch, (chr_ptr - str_ptr + 1));
    } else {
        fprintf(stderr, "don't found char %c in %s\n", ch, str_ptr);
    }

    return 0;
}
