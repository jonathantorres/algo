#include <stdio.h>
#include "print_numbers.h"

void print_numbers(int *numbers, int length, bool items_sorted)
{
    char *sorted_msg = (items_sorted == true) ? "Sorted: " : "Unsorted: ";

    printf("%s", sorted_msg);

    for (int i = 0; i < length; i++) {
        printf("%d ", *numbers);
        numbers++;
    }

    printf("\n");
}
