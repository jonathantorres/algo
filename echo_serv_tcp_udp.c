#include <ctype.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

// an echo server that uses select()
// to serve it's clients via a TCP socket
// and an UDP socket

#define BUFF_SIZE 2048

#ifndef max
    #define max(a,b) ((a) > (b) ? (a) : (b))
#endif

void handle_client(int clifd);
void capitalize(char *buff);
void sighandler(int signo);

int main(void)
{
    int servfd, clifd, udpfd, maxfdp1;
    struct sockaddr_in servaddr, cliaddr;
    int on = 1;
    fd_set rset;
    char buff[BUFF_SIZE];

    memset(buff, 0, BUFF_SIZE);
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // create listening socket
    if ((servfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket() error");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9090);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (setsockopt(servfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        perror("setsockopt() error");
        exit(EXIT_FAILURE);
    }

    if (bind(servfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind() error");
        exit(EXIT_FAILURE);
    }

    if (listen(servfd, 1024) < 0) {
        perror("listen() error");
        exit(EXIT_FAILURE);
    }

    // create udp socket
    if ((udpfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("udp socket() error");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9090);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(udpfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("udp bind() error");
        exit(EXIT_FAILURE);
    }

    struct sigaction act;
    memset(&act, 0, sizeof(act));
    sigemptyset(&act.sa_mask);
    act.sa_handler = sighandler;

    if (sigaction(SIGCHLD, &act, NULL) < 0) {
        perror("sigaction() error");
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&rset);
    maxfdp1 = max(servfd, udpfd) + 1;

    int nready = 0;
    int n = 0;
    socklen_t cliaddr_len = 0;

    while (true) {
        FD_SET(servfd, &rset);
        FD_SET(udpfd, &rset);

        if ((nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) {
            if (errno == EINTR) {
                continue; // interrupted system call, let's try again
            } else {
                perror("select() error");
                exit(EXIT_FAILURE);
            }
        }

        if (FD_ISSET(servfd, &rset)) {
            cliaddr_len = sizeof(cliaddr);

            if ((clifd = accept(servfd, (struct sockaddr*)&cliaddr, &cliaddr_len)) < 0) {
                perror("accept() error");
                exit(EXIT_FAILURE);
            }

            if (fork() == 0) {
                // child process
                close(servfd);
                handle_client(clifd);
                exit(EXIT_SUCCESS);
            }

            close(clifd);
        }

        if (FD_ISSET(udpfd, &rset)) {
            cliaddr_len = sizeof(cliaddr);

            n = recvfrom(udpfd, buff, BUFF_SIZE, 0, (struct sockaddr *)&cliaddr, &cliaddr_len);

            if (n < 0) {
                perror("recvfrom() error");
                exit(EXIT_FAILURE);
            }

            if (sendto(udpfd, buff, n, 0, (struct sockaddr *)&cliaddr, cliaddr_len) < 0) {
                perror("sendto() error");
                exit(EXIT_FAILURE);
            }
        }
    }
    return 0;
}

void capitalize(char *buff)
{
    for (int i = 0; i < (int)strlen(buff); i++) {
        buff[i] = toupper(buff[i]);
    }
}

void handle_client(int cli_fd)
{
    char recv_buf[BUFF_SIZE];
    memset(recv_buf, 0, BUFF_SIZE);
    int r;

    while (true) {
        r = read(cli_fd, &recv_buf, BUFF_SIZE);

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
        r = write(cli_fd, recv_buf, r);

        if (r < 0) {
            perror("write() error");
            close(cli_fd);
            return;
        }
        memset(recv_buf, 0, BUFF_SIZE);
    }
    close(cli_fd);
}

void sighandler(int signo)
{
    if (signo != SIGCHLD) {
        return;
    }

    int statloc = 0;

    while (waitpid(-1, &statloc, WNOHANG) > 0) {
        // do nothing
    }
    return;
}

