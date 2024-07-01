// Understanding the Machine: Section 2.2.3.1
// Convert a number to a binary string
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *n2b(int n);
char *reverse(char *s);

int main(void)
{
    int n = 44;
    char *res = n2b(n);
    if (res) {
        printf("%d = %s\n", n, res);
        free(res);
    }
    return 0;
}

char *n2b(int n)
{
    char *res = malloc(256); // arbitrary
    if (!res) {
        return NULL;
    }
    memset(res, 0, 256);
    float num = (float)n;
    int i = 0;
    while (num >= 1) {
        if (((int)num) % 2 == 0) {
            res[i] = '0';
        } else {
            res[i] = '1';
        }
        num = num/2;
        i++;
    }
    res[i] = '\0';
    res = reverse(res);
    return res;
}

char *reverse(char *s)
{
    int len = strlen(s);
    for (int i = (int)len-1, j = 0; i >= j; i--, j++) {
        char tmp = s[j];
        s[j] = s[i];
        s[i] = tmp;
    }
    return s;
}
