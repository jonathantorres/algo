#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Simple demonstration of unbuffered I/O
// with read() and write() to read from standard input
// and write into standard output

#define BUFSIZE 1024

int main(void)
{
    int n;
    char buf[BUFSIZE];

    memset(buf, 0, BUFSIZE);

    while ((n = read(STDIN_FILENO, buf, BUFSIZE)) > 0) {
        if ((n = write(STDOUT_FILENO, buf, n)) < 0) {
            perror("write() error");
            return 1;
        }
    }

    if (n < 0) {
        perror("read() error");
        return 1;
    }

    return 0;
}
