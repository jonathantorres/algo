#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// simple program that copies standard
// input to standard output

#define MAXLINE 1024

int main(void)
{
    char buf[MAXLINE];

    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (fputs(buf, stdout) == EOF) {
            perror("output error");
            exit(EXIT_FAILURE);
        }
    }
    if (ferror(stdin)) {
        perror("input error");
        exit(EXIT_FAILURE);
    }
    return 0;
}

