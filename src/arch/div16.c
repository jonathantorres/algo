// Understanding the Machine: Section 3.4.2
// Testing a set of bits for zero/not zero using AND
#include <stdio.h>

int main(void)
{
    // check if a number is divisible by 16
    // by checking if it's LO 4 bits are all set to 0
    int n = 32;

    if ((n & 0xf) == 0) {
        printf("%d is divisible by 16\n", n);
    } else {
        printf("%d is not divisible by 16\n", n);
    }
    return 0;
}
