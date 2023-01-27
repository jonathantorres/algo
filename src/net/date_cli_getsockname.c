#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// a very simple daytime client
// this client will print the local address and port
// of the client, after it connects to the server successfully

#define MAXLINE 1024

int main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    char locaddr_str[INET_ADDRSTRLEN];
    struct sockaddr_in servaddr, locaddr;

    if (argc != 2) {
        fprintf(stderr, "usage: date_cli_getsockname <IPaddress>\n");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(9090);
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        fprintf(stderr, "inet_pton error for %s\n", argv[1]);
        exit(1);
    }

    if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        perror("connect error");
        exit(1);
    }

    memset(&locaddr, 0, sizeof(locaddr));
    unsigned long loc_addr_size = sizeof(locaddr);
    socklen_t *loc_addr_siz = (socklen_t*)&loc_addr_size;

    if (getsockname(sockfd, (struct sockaddr*) &locaddr, loc_addr_siz) < 0) {
        perror("getsockname error");
        exit(1);
    }

    if (inet_ntop(AF_INET, &locaddr.sin_addr, locaddr_str, sizeof(locaddr_str)) == NULL) {
        perror("ntop error");
        exit(1);
    }

    printf("Local IP: %s, local port: %d\n", locaddr_str, ntohs(locaddr.sin_port));

    while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF) {
            perror("fputs error");
        }
    }
    if (n < 0) {
        perror("read error");
    }

    exit(0);
}
