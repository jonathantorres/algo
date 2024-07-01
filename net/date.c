#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// program to print the current date/time
// similar to the way that the date command does
#define MAXLINE 1024

int main(void)
{
    time_t caltime;
    struct tm *tm;
    char line[MAXLINE];

    if ((caltime = time(NULL)) < 0) {
        perror("time error");
        exit(EXIT_FAILURE);
    }
    if ((tm = localtime(&caltime)) == NULL) {
        perror("localtime error");
        exit(EXIT_FAILURE);
    }
    if (strftime(line, MAXLINE, "%a %d %b %Y %X %Z\n", tm) == 0) {
        perror("strftime error");
        exit(EXIT_FAILURE);
    }
    printf("%s", line);
    return 0;
}

