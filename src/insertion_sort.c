#include <stdio.h>
#include <stdbool.h>
#include "print_numbers.h"

#define LENGTH 10

int items[LENGTH] = { 4, 9, 3, 11, 55, 4, 12, 78, 16, 22 };

int main(int argc, char const *argv[])
{
    print_numbers(items, LENGTH, false);

    int i = 1;
    while (i < LENGTH) {
        int j = i;
        while (j > 0 && items[j - 1] > items[j]) {
            int tmp = items[j];
            items[j] = items[j - 1];
            items[j - 1] = tmp;
            j--;
        }
        i++;
    }

    print_numbers(items, LENGTH, true);
    return 0;
}
