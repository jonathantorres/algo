#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>

int main(void)
{
    int tcpsock, udpsock;
    int bufval = 0;
    socklen_t bufvalsiz = sizeof(bufval);

    if ((tcpsock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket() error");
        exit(1);
    }

    if ((udpsock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket() error");
        exit(1);
    }

    // tcp send buffer
    if (getsockopt(tcpsock, SOL_SOCKET, SO_SNDBUF, &bufval, &bufvalsiz) < 0) {
        perror("error getting tcp send buffer option");
        exit(1);
    }
    printf("tcp send buffer = %d\n", bufval);

    // tcp recv buffer
    if (getsockopt(tcpsock, SOL_SOCKET, SO_RCVBUF, &bufval, &bufvalsiz) < 0) {
        perror("error getting tcp receive buffer option");
        exit(1);
    }
    printf("tcp receive buffer = %d\n", bufval);

    // udp send buffer
    if (getsockopt(udpsock, SOL_SOCKET, SO_SNDBUF, &bufval, &bufvalsiz) < 0) {
        perror("error getting udp send buffer option");
        exit(1);
    }
    printf("udp send buffer = %d\n", bufval);

    // udp recv buffer
    if (getsockopt(udpsock, SOL_SOCKET, SO_RCVBUF, &bufval, &bufvalsiz) < 0) {
        perror("error getting udp receive buffer option");
        exit(1);
    }
    printf("udp receive buffer = %d\n", bufval);

    return 0;
}
