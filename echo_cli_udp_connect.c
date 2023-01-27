#include <arpa/inet.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// This is a simple udp echo client, this one uses
// connect() to assign the an address to it's socket
// it reads a line of text from standard input
// and it sends it to the udp server, then
// it waits for the datagram response from the client

#define BUFF_SIZE 1024

int main(void)
{
    int fd;
    struct sockaddr_in serv_addr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (fd < 0) {
        perror("socket() error");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9090);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) != 1) {
        perror("inet_pton() error");
        exit(EXIT_FAILURE);
    }

    if (connect(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect() error");
        exit(EXIT_FAILURE);
    }

    char buff[BUFF_SIZE];
    int n;

    while (true) {
        memset(buff, 0, BUFF_SIZE);

        if (fgets(buff, BUFF_SIZE, stdin) == NULL) {
            fprintf(stderr, "we are done\n");
            break;
        }
        n = strlen(buff);

        if (write(fd, buff, n) < 0) {
            perror("write() error");
            exit(EXIT_FAILURE);
        }

        memset(buff, 0, BUFF_SIZE);
        if (read(fd, buff, BUFF_SIZE) < 0) {
            perror("read() error");
            exit(EXIT_FAILURE);
        }

        fprintf(stdout, "%s", buff);
    }

    return 0;
}
