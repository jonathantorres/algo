#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024

// A daytime client that also prints
// the socket receive buffer and the MSS
// before and after the connection is made

int main(void)
{
    int serv_fd;
    struct sockaddr_in serv_addr;

    if ((serv_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9090);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int opt = 0;
    socklen_t opt_len = sizeof(int);

    if (getsockopt(serv_fd, SOL_SOCKET, SO_RCVBUF, &opt, &opt_len) < 0) {
        perror("getsockopt() error");
        exit(1);
    }
    printf("socket receive buffer: %d\n", opt);

    if (getsockopt(serv_fd, IPPROTO_TCP, TCP_MAXSEG, &opt, &opt_len) < 0) {
        perror("getsockopt() error");
        exit(1);
    }
    printf("socket max segment size: %d\n", opt);

    if (connect(serv_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect error");
        exit(1);
    }
    puts("connected ok");

    if (getsockopt(serv_fd, SOL_SOCKET, SO_RCVBUF, &opt, &opt_len) < 0) {
        perror("getsockopt() error");
        exit(1);
    }
    printf("socket receive buffer: %d\n", opt);

    if (getsockopt(serv_fd, IPPROTO_TCP, TCP_MAXSEG, &opt, &opt_len) < 0) {
        perror("getsockopt() error");
        exit(1);
    }
    printf("socket max segment size: %d\n", opt);

    char buff[BUFSIZE];
    memset(buff, 0, BUFSIZE);

    int rc = read(serv_fd, &buff, sizeof(buff));
    if (rc == 0) {
        fprintf(stderr, "Connection closed\n");
        exit(0);
    }
    if (rc < 0) {
        perror("read error");
        exit(1);
    }

    buff[rc] = '\0';
    fprintf(stdout, "%s", buff);
    close(serv_fd);

    return 0;
}
