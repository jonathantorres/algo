#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SEQFILE "./seqno"
#define MAXBUF 100

void my_lock(int fd);
void my_unlock(int fd);

int main(void)
{
    int fd, i, n, seqno;
    pid_t pid;
    char buff[MAXBUF+1];

    pid = getpid();

    if ((fd = open(SEQFILE, 2)) < 0) {
        perror("error opening file");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 20; i++) {
        my_lock(fd);
        lseek(fd, 0L, 0);

        if ((n = read(fd, buff, MAXBUF)) <= 0) {
            perror("read error");
            exit(EXIT_FAILURE);
        }
        buff[n] = '\0';

        if ((n = sscanf(buff, "%d\n", &seqno)) != 1) {
            perror("scanf error");
            exit(EXIT_FAILURE);
        }
        printf("pid = %d, seq# = %d\n", pid, seqno);
        seqno++;

        sprintf(buff, "%03d\n", seqno);
        n = strlen(buff);
        lseek(fd, 0L, 0);

        if (write(fd, buff, n) != n) {
            perror("write error");
            exit(EXIT_FAILURE);
        }
        my_unlock(fd);
    }
    return 0;
}

void my_lock(int fd)
{
    lseek(fd, 0L, 0);
    if (lockf(fd, F_LOCK, 0L) == -1) {
        perror("error locking file");
        exit(EXIT_FAILURE);
    }
}

void my_unlock(int fd)
{
    lseek(fd, 0L, 0);
    if (lockf(fd, F_ULOCK, 0L) == -1) {
        perror("error unlocking file");
        exit(EXIT_FAILURE);
    }
}
