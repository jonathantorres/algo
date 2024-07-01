// Understanding the Machine: Section 3.4.1
// Testing bits in a bit string using AND
#include <stdio.h>

int main(void)
{
    // check if a number is odd or even by testing it's LO bit
    int n = 55;

    if ((n & 1) != 0) {
        printf("%d is odd\n", n);
    } else {
        printf("%d is even\n", n);
    }
    return 0;
}
