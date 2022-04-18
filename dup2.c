#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// a very simple implementation of dup2
// this implementation will not cleanup
// the leftover fd's that were in-between fd and fd2

int Dup2(int fd, int fd2);

int main(void)
{
    int n;
    if ((n = Dup2(STDOUT_FILENO, 5)) < 0) {
        perror("dup error");
        exit(1);
    }
    printf("fd: %d\n", n);
    return 0;
}

int Dup2(int fd, int fd2)
{
    if (fd == fd2) {
        return fd2;
    }
    close(fd2);

    int nfd;
    while (true) {
        nfd = dup(fd);
        if (nfd < 0) {
            return -1;
        }
        if (nfd == fd2) {
            return nfd;
        }
    }
    errno = EINVAL;
    return -1;
}
