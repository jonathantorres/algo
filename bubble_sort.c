#include <stdio.h>
#include <stdbool.h>
#include "print_numbers.h"

#define LENGTH 10

int main(void)
{
    int items[LENGTH] = { 4, 9, 3, 11, 55, 4, 12, 78, 16, 22 };
    bool swapped = false;
    int times_through = 0;

    print_numbers(items, LENGTH, false);

    do {
        swapped = false;
        times_through++;
        for (int i = 1; i < LENGTH; i++) {
            if (items[i - 1] > items[i]) {
                int tmp = items[i];
                items[i] = items[i - 1];
                items[i - 1] = tmp;
                swapped = true;
            }
        }
    } while (swapped == true);

    print_numbers(items, LENGTH, true);
    printf("Times through: %d\n", times_through);

    return 0;
}
