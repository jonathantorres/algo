// a custom implementation of the system() syscall

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int _system(char *cmd);

int main(void)
{
    _system("date");
    return 0;
}

void sig_handler()
{
    // doing nothing
}

int _system(char *cmd)
{
    pid_t pid;

    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    if ((pid = fork()) == 0) {
        // child
        execl("/bin/bash", "bash", "-c", cmd, (char *)NULL);
        return 0;
    } else if (pid > 0) {
        // parent
        int s;
        signal(SIGCHLD, sig_handler);
        wait(&s);
        return 0;
    } else {
        return -1;
    }
}
