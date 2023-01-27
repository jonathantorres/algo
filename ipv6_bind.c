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
    struct sockaddr_in6 addr;

    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(PORT);

    if (inet_pton(AF_INET6, "::1", &addr.sin6_addr) < 1) {
        perror("inet_pton() error");
        exit(1);
    }

    if ((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
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

    printf("ipv6: listening on port %d\n", PORT);

    if (pause() < 0) {
        perror("pause() returned");
    }

    return 0;
}
