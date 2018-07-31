#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int s[2];
    int r = socketpair(AF_UNIX, SOCK_STREAM, 0, s);
    if (r < 0) {
        perror("socketpair error");
        exit(1);
    }

    if (fork()) {
        int val = 0;
        close(s[0]);
        while (1) {
            sleep(1);
            fprintf(stdout, "send data: %d\n", val);
            write(s[1], &val, sizeof(val));
            read(s[1], &val, sizeof(val));
            fprintf(stdout, "reveive data: %d\n", val);
        }
    } else {
        int val = 0;
        close(s[1]);
        while (1) {
            read(s[0], &val, sizeof(val));
            val++;
            write(s[0], &val, sizeof(val));
        }
    }

    return 0;
}
