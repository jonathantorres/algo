// Understanding the Machine: Section 3.4.3
// Comparing a set of bits within a binary string
#include <stdio.h>
#include <stdbool.h>

bool check_bits(int v1, int v2);

int main(void)
{
    int v1 = 55;
    int v2 = 65;

    if (check_bits(v1, v2)) {
        printf("bits 31, 24, 16, 10, 1, and 0 of %d and %d are equal\n", v1, v2);
    } else {
        printf("bits 31, 24, 16, 10, 1, and 0 of %d and %d are NOT equal\n", v1, v2);
    }

    v1 = 175564653;
    v2 = 184430553;
    if (check_bits(v1, v2)) {
        printf("bits 31, 24, 16, 10, 1, and 0 of %d and %d are equal\n", v1, v2);
    } else {
        printf("bits 31, 24, 16, 10, 1, and 0 of %d and %d are NOT equal\n", v1, v2);
    }

    return 0;
}

bool check_bits(int v1, int v2)
{
    if ((v1 & 0x81010403) == (v2 & 0x81010403)) {
        return true;
    }
    return false;
}
