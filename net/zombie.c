#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// program to illustrate the creation of a zombie process

#define PS "ps -o pid,ppid,state,tty,command"

int main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // this is the child
        exit(EXIT_SUCCESS);
    }

    // parent
    sleep(4);
    system(PS);
    exit(EXIT_SUCCESS);
    return 0;
}
