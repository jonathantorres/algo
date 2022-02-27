#include <stdio.h>


int main(void)
{
    union {
        short n;
        char m[sizeof(short)];
    } un;

    un.n = 0x0102;

    if (sizeof(short) == 2) {
        if (un.m[0] == 1 && un.m[1] == 2) {
            printf("big endian\n");
        } else if (un.m[0] == 2 && un.m[1] == 1) {
            printf("little endian\n");
        } else {
            printf("unknown");
        }
    } else {
        printf("sizeof(short) = %ld\n", sizeof(short));
    }
    return 0;
}
