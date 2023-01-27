#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

// program to print system information from uname
// similar to the output of the uname command

int main(void)
{
    struct utsname name;

    if (uname(&name) < 0) {
        perror("uname error");
        exit(EXIT_FAILURE);
    }
    printf("sysname = %s\n", name.sysname);
    printf("nodename = %s\n", name.nodename);
    printf("release = %s\n", name.release);
    printf("version = %s\n", name.version);
    printf("machine = %s\n", name.machine);
    return 0;
}

