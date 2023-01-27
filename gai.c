#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

// Program to demonstrate the use of getaddrinfo
// this call only asks for IPv4 addresses

#define ADDR_LEN 512

int main(void)
{
    int rc;
    struct addrinfo h;
    struct addrinfo *res = NULL;
    struct addrinfo *ai = NULL;

    memset(&h, 0, sizeof(struct addrinfo));

    h.ai_family = AF_INET;
    h.ai_socktype = SOCK_STREAM;
    h.ai_flags = AI_CANONNAME;

    if ((rc = getaddrinfo("localhost", "80", &h, &res)) != 0) {
        printf("getaddrinfo() error: %s\n", gai_strerror(rc));
        exit(1);
    }

    for (ai = res; ai != NULL; ai = ai->ai_next) {
        char addr[INET_ADDRSTRLEN];
        struct sockaddr_in *addr_in = (struct sockaddr_in *) ai->ai_addr;
        if (inet_ntop(ai->ai_family, &addr_in->sin_addr, addr, sizeof(addr)) == NULL) {
            perror("inet_ntop() error");
            continue;
        }
        printf("ADDR: %s\n", addr);
    }

    freeaddrinfo(res);
    return 0;
}
