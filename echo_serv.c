#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXBUF 1024

// a very simple echo server
// it servers one client at a time
// no forking involved

void serve_client(int cli_fd);

int main(void)
{
    int serv_fd, cli_fd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_addr_siz;

    if ((serv_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket() error");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_addr_siz = (socklen_t)sizeof(cli_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9090);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serv_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind() error");
        exit(1);
    }

    if (listen(serv_fd, 10) < 0) {
        perror("listen() error");
        exit(1);
    }

    while (true) {
        if ((cli_fd = accept(serv_fd, (struct sockaddr *) &cli_addr, &cli_addr_siz)) < 0) {
            perror("accept() error");
            continue;
        }

        // simple example, serve 1 client at a time
        serve_client(cli_fd);
    }

    return 0;
}

void capitalize(char *buff)
{
    for (int i = 0; i < (int)strlen(buff); i++) {
        buff[i] = toupper(buff[i]);
    }
}

void serve_client(int cli_fd)
{
    char recv_buf[MAXBUF];
    memset(recv_buf, 0, MAXBUF);
    int r;

    while (true) {
        r = read(cli_fd, &recv_buf, MAXBUF);

        if (r < 0) {
            perror("read() error");
            close(cli_fd);
            break;
        }

        if (r == 0) {
            fprintf(stderr, "read() returned 0\n");
            close(cli_fd);
            break;
        }

        recv_buf[r] = '\0';
        capitalize(recv_buf);
        r = write(cli_fd, recv_buf, MAXBUF);

        if (r < 0) {
            perror("write() error");
            close(cli_fd);
            return;
        }
        memset(recv_buf, 0, MAXBUF);
    }
    close(cli_fd);
}
