#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>

#define BUF_SIZE 2048
#define ADDR_LEN 512

int main(void)
{
    int cli_fd;
    char buf[BUF_SIZE];
    char ipaddr[ADDR_LEN];
    ssize_t n;
    struct hostent *hptr;
    char **addrptr;
    struct sockaddr_in serv_addr, serv_recv_addr;
    socklen_t serv_recv_addr_siz = sizeof(serv_recv_addr);

    memset(&ipaddr, 0, ADDR_LEN);
    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&serv_recv_addr, 0, sizeof(serv_recv_addr));
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
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            fprintf(stderr, "we are done\n");
            break;
        }

        n = sendto(cli_fd, buf, sizeof(buf), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        if (n < 0) {
            perror("sendto() error");
            continue;
        }

        memset(buf, 0, sizeof(buf));

        n = recvfrom(cli_fd, buf, sizeof(buf), 0, (struct sockaddr*)&serv_recv_addr, &serv_recv_addr_siz);
        if (n < 0) {
            perror("recvfrom() error");
            continue;
        }

        fprintf(stdout, "Reply: %s", buf);
        if ((hptr = gethostbyaddr(&serv_recv_addr.sin_addr, serv_recv_addr_siz, serv_recv_addr.sin_family)) == NULL) {
            herror("gethostbyaddr() error");
        } else {
            if ((hptr = gethostbyname(hptr->h_name)) == NULL) {
                herror("gethostbyname() error");
            } else {
                addrptr = hptr->h_addr_list;
                for (; *addrptr != NULL; addrptr++) {
                    if (inet_ntop(hptr->h_addrtype, *addrptr, ipaddr, ADDR_LEN) == NULL) {
                        perror("inet_ntop() error");
                        continue;
                    }
                    printf("Server IP Address: %s\n", ipaddr);
                }
            }
        }

        memset(buf, 0, sizeof(buf));
    }
    return 0;
}
