#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

void sig_handler(int sig);

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2) {
        fprintf(stderr, "usage: tcpcli <IP>\n");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13); // daytime server

    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 1) {
        perror("inet_pton error");
        exit(1);
    }

    // signal handling
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGPIPE, &sa, NULL) == -1) {
        perror("sigaction error");
        exit(1);
    }

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect error");
        exit(1);
    }

    sleep(2);
    if (write(sockfd, "hello", 5) == -1) {
        perror("write error");
    }
    sleep(2);
    if (write(sockfd, "world", 5) == -1) {
        perror("write2 error");
    }
    exit(0);
}

void sig_handler(int sig)
{
    if (sig == SIGPIPE) {
        printf("SIGPIPE received\n");
    }
    return;
}
