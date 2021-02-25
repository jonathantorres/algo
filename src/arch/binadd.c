// Understanding the Machine: Section 3.1.1
// Adding binary values
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char *binadd(char *b1, char *b2);

int main(void)
{
    char *b1 = "00000010";
    char *b2 = "00000010";
    char *res = binadd(b1, b2);

    if (res) {
        printf("%s + %s = %s\n", b1, b2, res);
        free(res);
    }
    return 0;
}

char *binadd(char *b1, char *b2)
{
    if (strlen(b1) != 8 || strlen(b2) != 8) {
        return NULL;
    }

    char *res = malloc(9); // only 8 bit values
    if (!res) {
        return NULL;
    }
    memset(res, 0, 9);

    bool carry = false;
    for (int i = 7; i >= 0; i--) {
        if (carry) {
            if (b1[i] == '0' && b2[i] == '0') {
                res[i] = '1';
                carry = false;
            } else if (b1[i] == '0' && b2[i] == '1') {
                res[i] = '0';
            } else if (b1[i] == '1' && b2[i] == '0') {
                res[i] = '0';
            } else {
                res[i] = '1';
            }
        } else {
            if (b1[i] == '0' && b2[i] == '0') {
                res[i] = '0';
            } else if (b1[i] == '0' && b2[i] == '1') {
                res[i] = '1';
            } else if (b1[i] == '1' && b2[i] == '0') {
                res[i] = '1';
            } else {
                res[i] = '0';
                carry = true;
            }
        }
    }
    res[8] = '\0';
    return res;
}
