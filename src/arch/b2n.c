// Understanding the Machine: Section 2.2.3.1
// Convert a binary string to a number
#include <stdio.h>
#include <string.h>
#include <math.h>

int b2n(char *bin);

int main(void)
{
    char *bin = "101100";
    int n = b2n(bin);
    printf("%s = %d\n", bin, n);
    return 0;
}

int b2n(char *bin)
{
    // note: we are not validating the string
    int len = strlen(bin);
    int n = 0;
    for (int i = (int)len-1, pos = 0; i >= 0; i--, pos++) {
        if (bin[i] == '0') {
            continue;
        }
        double res = exp2((double)pos);
        n += (int)res;
    }
    return n;
}
