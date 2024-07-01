#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>

// A simple echo client that uses select() to
// handle the file descriptor that deals with user input
// and the socket file descriptor

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
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    socklen_t serv_addr_siz = sizeof(serv_addr);

    if (connect(serv_fd, (struct sockaddr *) &serv_addr, serv_addr_siz) < 0) {
        perror("connect() error");
        exit(1);
    }

    char line[MAXLINE];
    char recv_buf[MAXBUF];
    int r;
    memset(line, 0, MAXLINE);

    fd_set rfds;
    int max = 0;
    bool stdineof = false;

    while (true) {
        max = serv_fd;
        FD_ZERO(&rfds);
        FD_SET(serv_fd, &rfds);

        if (!stdineof) {
            FD_SET(fileno(stdin), &rfds);

            if (fileno(stdin) > max) {
                max = fileno(stdin);
            }
        }

        if (select(max+1, &rfds, NULL, NULL, NULL) < 0) {
            perror("select() error");
            break;
        }

        // input is ready
        if (FD_ISSET(fileno(stdin), &rfds) != 0) {
            if (fgets(line, sizeof(line), stdin) == NULL) {
                stdineof = true;
                if (shutdown(serv_fd, SHUT_WR) < 0) {
                    perror("shutdown() error");
                    break;
                }
                FD_CLR(fileno(stdin), &rfds);
                fprintf(stderr, "stdin closed\n");
                continue;
            }

            if (write(serv_fd, line, sizeof(line)) < 0) {
                perror("write() error");
                break;
            }
        }

        // connection is ready
        if (FD_ISSET(serv_fd, &rfds) != 0) {
            r = read(serv_fd, &recv_buf, MAXBUF);

            if (r < 0) {
                perror("read() error");
                break;
            }
            if (r == 0) {
                if (!stdineof) {
                    fprintf(stderr, "server terminated prematurely\n");
                }
                break;
            }

            recv_buf[r] = '\0';

            fprintf(stdout, "%s", recv_buf);
        }
    }

    return 0;
}

