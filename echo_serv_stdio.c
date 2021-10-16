#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXBUF 1024

void serve_client(int cli_fd);

int main(void)
{
    int serv_fd, cli_fd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_addr_siz;

    if ((serv_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket() error");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_addr_siz = (socklen_t)sizeof(cli_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9090);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serv_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind() error");
        exit(1);
    }

    if (listen(serv_fd, 10) < 0) {
        perror("listen() error");
        exit(1);
    }

    while (true) {
        if ((cli_fd = accept(serv_fd, (struct sockaddr *) &cli_addr, &cli_addr_siz)) < 0) {
            perror("accept() error");
            continue;
        }

        // simple example, serve 1 client at a time
        serve_client(cli_fd);
    }

    return 0;
}

void capitalize(char *buff)
{
    if (!buff) {
        return;
    }
    for (int i = 0; i < (int)strlen(buff); i++) {
        buff[i] = toupper(buff[i]);
    }
}

void serve_client(int cli_fd)
{
    char recv_buf[MAXBUF];
    memset(recv_buf, 0, MAXBUF);
    FILE *fpin, *fpout;

    if ((fpin = fdopen(cli_fd, "r")) == NULL) {
        perror("fdopen() input error");
        return;
    }

    if ((fpout = fdopen(cli_fd, "w")) == NULL) {
        perror("fdopen() output error");
        return;
    }

    while (true) {
        if (fgets(recv_buf, MAXBUF, fpin) == NULL) {
            fprintf(stderr, "fgets() returned NULL\n");
            break;
        }
        capitalize(recv_buf);

        if (fputs(recv_buf, fpout) == EOF) {
            perror("fputs()");
            break;
        }
        fflush(fpout);
    }
    close(cli_fd);
}
