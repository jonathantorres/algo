#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

// program that demostrate the use of the atexit() function
// this will register functions that will execute when
// the program terminates normally

static void my_exit1(void);
static void my_exit2(void);

int main(void)
{
    if (atexit(my_exit2) != 0) {
        perror("atexit error");
        exit(EXIT_FAILURE);
    }
    if (atexit(my_exit1) != 0) {
        perror("atexit error");
        exit(EXIT_FAILURE);
    }
    if (atexit(my_exit1) != 0) {
        perror("atexit error");
        exit(EXIT_FAILURE);
    }
    printf("main is now done\n");
    return 0;
}

static void my_exit1(void)
{
    printf("first exit handler\n");
}

static void my_exit2(void)
{
    printf("second exit handler\n");
}
