#include <stdio.h>

// simple program to illustrate the use
// of a pointer to a value that is out of scope

int f1(int val);

int main(void)
{
    printf("%d\n", f1(1));
    printf("%d\n", f1(0));
    return 0;
}

int f1(int val)
{
    int num = 0;
    int *ptr = &num;

    if (val == 0) {
        int val;
        val = 5;
        ptr = &val;
    }
    return (*ptr + 1);
}
