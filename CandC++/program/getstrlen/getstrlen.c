#include <stdio.h>
#include <string.h>

static int get_str_len(const char * buf, int buflen)
{
    const char *s, *e;
    int len = 0;

    for (s = buf, e = buf + buflen - 1; len >= 0, s < e; s++) {
        if (s[0] == '\n' && s[1] == '\r' && s[2] == '\n') {
            len = (int) (s - buf + 3);
        }
    }

    return len;
}


int main(int argc, char *agrv[])
{
    const char *str = "hello world\r\n\r\n";
    int str_len = 0;
    str_len = strlen(str);
    printf("The length of str (strlen) is : %d\n", str_len);

    str_len = get_str_len(str, str_len);
    printf("The length of str (get_str_len) is : %d \n", str_len);

    return 0;
}
