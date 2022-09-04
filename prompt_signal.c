#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// A very simple shell like program
// that will execute the program we provide
// in a child process, this program does not stop
// when we send the SIGINT signal

void sig_int(int signo);

#define BUFSIZE 1024

int main(void)
{
    int status;
    char buf[BUFSIZE];
    pid_t pid;

    if (signal(SIGINT, sig_int) == SIG_ERR) {
        perror("signal() error");
        exit(1);
    }

    memset(buf, 0, BUFSIZE);
    printf("%% ");
    while (fgets(buf, BUFSIZE, stdin) != NULL) {
        // replace newline with NULL character
        if (buf[strlen(buf)-1] == '\n') {
            buf[strlen(buf)-1] = 0;
        }
        if ((pid = fork()) < 0) {
            perror("fork() error");
            return 1;
        } else if (pid == 0) {
            // this is the child
            execlp(buf, buf, (char *)0);
            perror("could not execute execlp");
            exit(127);
        }

        // parent process
        if ((pid = waitpid(pid, &status, 0)) < 0) {
            perror("waitpid() error");
            return 1;
        }
        printf("%% ");
    }
    printf("\n");

    return 0;
}

void sig_int(int signo)
{
    if (signo) {} // get rid of the compiler warning
    printf("interrupt\n%% ");
}
