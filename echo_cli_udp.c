#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdbool.h>

// This is a simple udp echo client
// it reads a line of text from standard input
// and it sends it to the udp server, then
// it waits for the datagram response from the client

#define BUF_SIZE 2048

int main(void)
{
    int cli_fd;
    char buf[BUF_SIZE];
    ssize_t n;
    struct sockaddr_in serv_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9090);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) != 1) {
        perror("inet_pton() error");
        exit(1);
    }

    if ((cli_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket() error");
        exit(1);
    }

    while (true) {
        if (fgets(buf, BUF_SIZE, stdin) == NULL) {
            fprintf(stderr, "we are done\n");
            break;
        }
        n = strlen(buf);

        n = sendto(cli_fd, buf, n, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        if (n < 0) {
            perror("sendto() error");
            continue;
        }

        memset(buf, 0, BUF_SIZE);

        n = recvfrom(cli_fd, buf, BUF_SIZE, 0, NULL, NULL);
        if (n < 0) {
            perror("recvfrom() error");
            continue;
        }

        fprintf(stdout, "%s", buf);
        memset(buf, 0, BUF_SIZE);
    }
    return 0;
}
