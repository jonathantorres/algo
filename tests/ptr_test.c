#include <stdio.h>
#include <stdlib.h>

typedef struct point {
    int x;
    int y;
} point;

typedef struct head {
    int top;
    int bottom;
    int left;
    int right;
    char *name;
} head;

int main(void)
{
    // printf("%lu\n", sizeof(void*));
    // printf("%lu\n", sizeof(int*));
    // printf("%lu\n", sizeof(int));
    // printf("%lu\n", sizeof(point*));
    // printf("%lu\n", sizeof(head*));

    return 0;
}
