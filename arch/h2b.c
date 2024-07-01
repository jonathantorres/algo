// Understanding the Machine: Section 2.2.4
// Convert a hexadecimal string into binary
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *hextable[] = {
    "0000", // 0
    "0001", // 1
    "0010", // 2
    "0011", // 3
    "0100", // 4
    "0101", // 5
    "0110", // 6
    "0111", // 7
    "1000", // 8
    "1001", // 9
    "1010", // A
    "1011", // B
    "1100", // C
    "1101", // D
    "1110", // E
    "1111"  // F
};

char *h2b(char *h);
void append_bin_chars(char *chars, char **res_p);

int main(void)
{
    char *h = "DEAD";
    char *b = h2b(h);
    if (b) {
        printf("%s = %s\n", h, b);
        free(b);
    }
    return 0;
}

char *h2b(char *h)
{
    // note: we are not validating the hex string
    int len = (int)strlen(h);
    int blen = len * 4;
    char *res = malloc(blen+1);
    if (!res) {
        return NULL;
    }
    memset(res, 0, blen+1);
    char *res_p = res;

    for (int i = 0; i < len; i++) {
        switch (h[i]) {
            case '0':
                append_bin_chars(hextable[0], &res_p);
                break;
            case '1':
                append_bin_chars(hextable[1], &res_p);
                break;
            case '2':
                append_bin_chars(hextable[2], &res_p);
                break;
            case '3':
                append_bin_chars(hextable[3], &res_p);
                break;
            case '4':
                append_bin_chars(hextable[4], &res_p);
                break;
            case '5':
                append_bin_chars(hextable[5], &res_p);
                break;
            case '6':
                append_bin_chars(hextable[6], &res_p);
                break;
            case '7':
                append_bin_chars(hextable[7], &res_p);
                break;
            case '8':
                append_bin_chars(hextable[8], &res_p);
                break;
            case '9':
                append_bin_chars(hextable[9], &res_p);
                break;
            case 'A':
                append_bin_chars(hextable[10], &res_p);
                break;
            case 'B':
                append_bin_chars(hextable[11], &res_p);
                break;
            case 'C':
                append_bin_chars(hextable[12], &res_p);
                break;
            case 'D':
                append_bin_chars(hextable[13], &res_p);
                break;
            case 'E':
                append_bin_chars(hextable[14], &res_p);
                break;
            case 'F':
                append_bin_chars(hextable[15], &res_p);
                break;
        }
    }

    *res_p = '\0';
    return res;
}

void append_bin_chars(char *chars, char **res_p)
{
    for (int i = 0; i < (int)strlen(chars); i++) {
        **res_p = chars[i];
        (*res_p)++;
    }
}
