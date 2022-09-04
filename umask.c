#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// simple program that sets the umask
// before creating a file

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(void)
{
    umask(0);
    if (creat("foo", RWRWRW) < 0) {
        perror("creat error for foo");
        exit(1);
    }
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (creat("bar", RWRWRW) < 0) {
        perror("creat error for bar");
        exit(1);
    }
    return 0;
}
