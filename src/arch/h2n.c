// Understanding the Machine: Section 2.2.4
// Convert a hexadecimal string to a number
#include <stdio.h>
#include <string.h>
#include <math.h>

int h2n(char *h);

int hextable[16] = {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'A',
    'B',
    'C',
    'D',
    'E',
    'F' 
};

int main(void)
{
    char *h = "DEAD";
    int n = h2n(h);
    printf("%s = %d\n", h, n);
    return 0;
}

int h2n(char *h)
{
    // note: we are not validating the string
    int n = 0;
    int len = strlen(h);
    for (int i = (int)len-1, pos = 0; i >= 0; i--, pos++) {
        int hex_i = 0;
        for (int j = 0; j < 16; j++) {
            if (hextable[j] == h[i]) {
                hex_i = j;
            }
        }
        n += (hex_i * (int)pow(16.0, (float)pos));
    }
    return n;
}
