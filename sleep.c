// a custom implementation of the sleep() syscall

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void _sleep(int s);

int main(void)
{
    fprintf(stderr, "start...");
    _sleep(3);
    printf("end\n");
    return 0;
}

int c = 0;

void handler()
{
    c = 1;
}

void _sleep(int s)
{
    alarm(s);
    signal(SIGALRM, handler);
    while (1) {
        if (c == 1) {
            break;
        }
    }
}
