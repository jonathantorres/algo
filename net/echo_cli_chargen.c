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

// a very simple tcp client
// it tries to connect to the chargen service
// to demonstrate the SHUT_RD option of shutdown()

int main(void)
{
    int serv_fd;
    struct sockaddr_in serv_addr;

    if ((serv_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket() error");
        exit(1);
    };

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(19);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    socklen_t serv_addr_siz = sizeof(serv_addr);

    if (connect(serv_fd, (struct sockaddr *) &serv_addr, serv_addr_siz) < 0) {
        perror("connect() error");
        exit(1);
    }

    pause();

    return 0;
}
