#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>

#define MAXLINE 1024
#define MAXBUF 1024

// Demonstrate the SIGPIPE signal when writing to a socket
// that has already received a FIN
// we do this by connecting this client to a daytime server
// and issuing two writes to it

void sig_handler(int n)
{
    if (n) {}
    printf("SIGPIPE signal\n");

    return;
}

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

    struct sigaction act;
    act.sa_handler = sig_handler;
    sigemptyset(&act.sa_mask);

    if (sigaction(SIGPIPE, &act, NULL) < 0) {
        perror("sigaction error");
        exit(1);
    }

    if (connect(serv_fd, (struct sockaddr *) &serv_addr, serv_addr_siz) < 0) {
        perror("connect() error");
        exit(1);
    }

    char *line = "This is a test";

    sleep(2);

    if (write(serv_fd, line, strlen(line)) < 0) {
        perror("error on first write");
        return 1;
    }

    sleep(2);

    if (write(serv_fd, line, sizeof(line)) < 0) {
        perror("error on second write");
        return 1;
    }

    return 0;
}
