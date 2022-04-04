#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <netinet/ip.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

// A very simple echo server
// that uses the standard I/O library
// for handling the client connection

#define MAXBUF 1024

void serve_client(int cli_fd);
void sighandler(int signo);

int main(void)
{
    int serv_fd, cli_fd, on;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_addr_siz;

    if ((serv_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket() error");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_addr_siz = (socklen_t)sizeof(cli_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9090);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        perror("setsockopt() error");
        exit(EXIT_FAILURE);
    }

    if (bind(serv_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind() error");
        exit(EXIT_FAILURE);
    }

    if (listen(serv_fd, 10) < 0) {
        perror("listen() error");
        exit(EXIT_FAILURE);
    }

    struct sigaction act;
    memset(&act, 0, sizeof(act));
    sigemptyset(&act.sa_mask);
    act.sa_handler = sighandler;
    pid_t pid;

    if (sigaction(SIGCHLD, &act, NULL) < 0) {
        perror("sigaction() error");
        exit(EXIT_FAILURE);
    }

    while (true) {
        if ((cli_fd = accept(serv_fd, (struct sockaddr *) &cli_addr, &cli_addr_siz)) < 0) {
            if (errno == EINTR) {
                continue; // interrupted system call, just continue
            } else {
                perror("accept() error");
                continue;
            }
        }

        pid = fork();
        if (pid > 0) {
            // parent
            close(cli_fd);
        } else if (pid == 0) {
            // child
            close(serv_fd);
            serve_client(cli_fd);
            exit(EXIT_SUCCESS);
        } else {
            perror("fork() error");
            continue;
        }
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

    if (setvbuf(fpin, recv_buf, _IOLBF, MAXBUF) != 0) {
        perror("setvbuf()");
        return;
    }

    if (setvbuf(fpout, recv_buf, _IOLBF, MAXBUF) != 0) {
        perror("setvbuf()");
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
    }
    fclose(fpin);
    fclose(fpout);
}

void sighandler(int signo)
{
    if (signo != SIGCHLD) {
        return;
    }

    int statloc = 0;

    while (waitpid(-1, &statloc, WNOHANG) > 0) {
        // do nothing
    }
    return;
}
