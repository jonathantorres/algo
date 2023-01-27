// two processes sending data to each other through a pipe
// the client reads a filename from standard input and writes it to the pipe
// the server reads the filename from the pipe, opens and reads the file
// and then sends the file contents through the pipe to the client
// the client reads the file contents from the pipe and writes the
// file contents to standard output
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXBUF 1024

void client(int readfd, int writefd);
void server(int readfd, int writefd);

int main(void)
{
    int childpid;
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) < 0 || pipe(pipe2) < 0) {
        perror("error creating pipe");
        exit(EXIT_FAILURE);
    }

    childpid = fork();
    if (childpid < 0) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (childpid > 0) {
        // parent
        close(pipe1[0]);
        close(pipe2[1]);

        client(pipe2[0], pipe1[1]);

        while (wait(NULL) != childpid) {
            // wait for child process
        }

        close(pipe1[1]);
        close(pipe2[0]);
        exit(EXIT_SUCCESS);
    } else {
        // child
        close(pipe1[1]);
        close(pipe2[0]);

        server(pipe1[0], pipe2[1]);

        close(pipe1[0]);
        close(pipe2[1]);
        exit(EXIT_SUCCESS);
    }
    return 0;
}

void client(int readfd, int writefd)
{
    char buff[MAXBUF];
    int n;

    if (fgets(buff, MAXBUF, stdin) == NULL) {
        perror("client: filename read error");
        exit(EXIT_FAILURE);
    }

    n = strlen(buff);
    if (buff[n-1] == '\n') {
        n--;
    }

    if (write(writefd, buff, n) != n) {
        perror("client: filename write error");
        exit(EXIT_FAILURE);
    }

    while ((n = read(readfd, buff, MAXBUF)) > 0) {
        if (write(1, buff, n) != n) {
            perror("client: data write error");
            exit(EXIT_FAILURE);
        }
    }

    if (n < 0) {
        perror("client: data read error");
        exit(EXIT_FAILURE);
    }
}

void server(int readfd, int writefd)
{
    char buff[MAXBUF];
    char errmessg[256];
    int n, fd;

    if ((n = read(readfd, buff, MAXBUF)) <= 0) {
        perror("server: filename read error");
        exit(EXIT_FAILURE);
    }
    buff[n] = '\0';

    if ((fd = open(buff, 0)) < 0) {
        sprintf(errmessg, ": can't open, %s\n", strerror(errno));
        strcat(buff, errmessg);
        n = strlen(buff);

        if (write(writefd, buff, n) != n) {
            perror("server: errmessg write error");
            exit(EXIT_FAILURE);
        }
    } else {
        while ((n = read(fd, buff, MAXBUF)) > 0) {
            if (write(writefd, buff, n) != n) {
                perror("server: data write error");
                exit(EXIT_FAILURE);
            }
        }
        if (n < 0) {
            perror("server: read error");
            exit(EXIT_FAILURE);
        }
    }
}
