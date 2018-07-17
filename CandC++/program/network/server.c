#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in s_addr, c_addr;
    int sockfd, connfd, addrlen, nread;
    char buf[1024];

    if (argc < 2) {
        fprintf(stdout, "Usage: port\n");
        exit(-1);
    }
    bzero(&s_addr, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(9999);
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        exit(-1);
    }

    if (bind(sockfd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0) {
        exit(-1);
    }

    if (listen(sockfd, 5) < 0) {
        exit(-1);
    }
    while (1) {
        fprintf(stdout, "start accept new connection\n");
        addrlen = sizeof(c_addr);
        connfd = accept(sockfd, (struct sockaddr *) &c_addr, &addrlen);
        fprintf(stdout, "accepted new connection\n");
        nread = read(connfd, buf, sizeof(buf));
        if (nread > 0) {
            fprintf(stdout, "%s\n", buf);
        } else {
            fprintf(stdout, "exit code %d\n", nread);
        }
        fflush(stdout);
        close(connfd);
    }
}
