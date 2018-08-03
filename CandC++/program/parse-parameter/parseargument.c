#include <stdio.h>

int parse_argv(int argc, char *const *argv)
{
    int i;
    char *p;

    for (i = 1; i < argc; i++) {
        p = argv[i];
        if (*p++ != '-') {
            printf("format error\n");
            return -1;
        }

        while (*p) {
            switch (*p++) {
            case 'a':
                //...
                break;
            case 'b':
                //...
                break;
            case 's':
                if (*p) {
                    // s = p
                    goto next;
                }
                // s = argv[i++];
                goto next;
            default:
                return -1;
            }
        }
next:
        continue;
    }
}


int main(int argc, char *argv[])
{
    parse_argv(argc, argv);
}
