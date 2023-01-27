#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// a very simple echo server with udp
// waits for a message from a client
// and then it capitalizes the message
// and sends it back to the client

#define BUF_SIZE 2048

void capitalize(char *buff);

int main(void)
{
    int serv_fd;
    struct sockaddr_in serv_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9090);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((serv_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket() error");
        exit(1);
    }

    if (bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind() error");
        exit(1);
    }

    char buf[BUF_SIZE];
    ssize_t n;
    struct sockaddr_in cli_addr;
    socklen_t cli_addr_siz = sizeof(cli_addr);

    memset(&cli_addr, 0, sizeof(cli_addr));

    while (true) {
        memset(&buf, 0, sizeof(buf));
        n = recvfrom(serv_fd, buf, BUF_SIZE, 0, (struct sockaddr*)&cli_addr, &cli_addr_siz);
        if (n < 0) {
            perror("recvfrom() error");
            continue;
        }
        capitalize(buf);

        n = sendto(serv_fd, buf, n, 0, (struct sockaddr*)&cli_addr, cli_addr_siz);
        if (n < 0) {
            perror("sendto() error");
            continue;
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
