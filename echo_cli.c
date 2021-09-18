#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>

#define MAXLINE 1024
#define MAXBUF 1024

int main(void)
{
    int serv_fd;
    struct sockaddr_in serv_addr;

    if ((serv_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket() error");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9090);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    socklen_t serv_addr_siz = sizeof(serv_addr);

    if (connect(serv_fd, (struct sockaddr *) &serv_addr, serv_addr_siz) < 0) {
        perror("connect() error");
        exit(1);
    }

    char line[MAXLINE];
    char recv_buf[MAXBUF];
    int r;
    memset(line, 0, MAXLINE);

    while (true) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            fprintf(stderr, "connection closed\n");
            break;
        }

        if (write(serv_fd, line, sizeof(line)) < 0) {
            perror("write() error");
            break;
        }

        r = read(serv_fd, &recv_buf, MAXBUF);

        if (r < 0) {
            perror("read() error");
            break;
        }
        if (r == 0) {
            break;
        }

        recv_buf[r] = '\0';

        fprintf(stdout, "%s", recv_buf);
    }
    
    return 0;
}
