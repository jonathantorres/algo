#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// a very simple daytime server

int main(void)
{
    int servfd, clifd;
    struct sockaddr_in serv_addr, cli_addr;

    if ((servfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&cli_addr, 0, sizeof(cli_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(9090);

    if (bind(servfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind error");
        exit(1);
    }

    if (listen(servfd, 10) < 0) {
        perror("listen error");
        exit(1);
    }
    
    unsigned long cli_siz = sizeof(cli_addr);
    socklen_t *cli_addr_siz = (socklen_t *) &cli_siz;

    while (true) {
        if ((clifd = accept(servfd, (struct sockaddr *) &cli_addr, cli_addr_siz)) < 0) {
            perror("accept error");
            continue;
        }

        time_t t = time(NULL);
        char *date_str = ctime(&t);
        if (write(clifd, date_str, strlen(date_str)) < 0) {
            perror("write error");
            close(clifd);
            continue;
        }

        close(clifd);
    }

    return 0;
}
