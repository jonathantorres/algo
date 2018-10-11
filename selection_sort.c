#include <stdio.h>
#include <stdbool.h>
#include "print_numbers.h"

#define LENGTH 10

int items[LENGTH] = { 4, 9, 3, 11, 55, 4, 12, 78, 16, 22 };

int main(void)
{
    print_numbers(items, LENGTH, false);

    for (int j = 0; j < LENGTH - 1; j++) {
        int min = j;

        for (int i = j + 1; i < LENGTH; i++) {
            if (items[i] < items[min]) {
                min = i;
            }
        }

        if (min != j) {
            int tmp = items[min];
            items[min] = items[j];
            items[j] = tmp;
        }
    }

    print_numbers(items, LENGTH, true);

    return 0;
}
