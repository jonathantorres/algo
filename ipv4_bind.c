#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <errno.h>

#define PORT 9090

int main(void)
{
    int sockfd;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) < 1) {
        perror("inet_pton() error");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket() error");
        exit(1);
    }

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind() error");
        exit(1);
    }

    if (listen(sockfd, 10) < 0) {
        perror("listen() error");
        exit(1);
    }

    printf("ipv4: listening on port %d\n", PORT);

    if (pause() < 0) {
        perror("pause() returned");
    }

    return 0;
}
