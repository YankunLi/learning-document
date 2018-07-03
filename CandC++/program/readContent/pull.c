#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <sys/socket.h>

static int pull(FILE *fp, int socket,  char *buf, int len);

int main(int argc, char *argv)
{
    FILE *fp = fopen("/temp/filename.txt", "r");
    if (!fp) {
        printf("Don't found file\n");
        return -1;
    }
   // int fd = open("/temp/filename.txt", O_RDWR|O_CREAT);
    int socket = 9, nread = 0; //need realy socket
    char buf[1024];
    nread = pull(fp, socket, buf, sizeof(buf));

    return 0;
}

static int pull(FILE *fp, int socket,  char *buf, int len)
{
     int nread = 0;

     if (fp != NULL) {
         nread = read(fileno(fp), buf, (size_t) len);
     }
#ifdef SOCKET
     else if (socket)
     {
         nread = (size_t) recv(socket, buf, (size_t) len, 0);
     }
    else
#endif
     {
        //
     }

     return nread;
}
