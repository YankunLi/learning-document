#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int signal_num)
{
    fprintf(stdout, "receive signal %d\n", signal_num);
}

int main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    char *buf = "GET / HTTP/1.1";
    int sock, n;
    if (argc < 3) {
        fprintf(stderr, "Usege: ip port\n");
        exit(-1);
    }
    signal(SIGPIPE, handle_signal);
    addr.sin_family = AF_INET;
//    addr.sin_port = htons(strtol(argv[2], NULL, 10));
    addr.sin_port = htons(9999);
    fprintf(stdout, "parameter : %s %s\n", argv[1], argv[2]);
    if (inet_pton(AF_INET, argv[1], &addr.sin_addr.s_addr) < 0) {
        fprintf(stderr, "transfer ip failed\n");
        exit(-1);
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        fprintf(stderr, "Create socket failed\n");
        exit(-1);
    }
    if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        fprintf(stderr, "connect server failed\n");
        exit(-1);
    }
    n = write(sock, buf, strlen(buf));
    fprintf(stdout, "send data length is : %d\n", n);
 //   n = send(sock, buf, strlen(buf), MSG_NOSIGNAL);
    if (n > 0) {
        fprintf(stdout, "send data length is : %d\n", n);
        fflush(stdout);
    } else {
        fprintf(stdout, "send data length is : %d\n", n);
    }
    fflush(stdout);

    return n;
}
