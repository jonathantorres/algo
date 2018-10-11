#include <stdio.h>
#include <stdbool.h>
#include "print_numbers.h"

void quicksort(int low, int hi);
int partition(int low, int hi);

#define LENGTH 10
int items[LENGTH] = { 4, 9, 3, 11, 55, 4, 12, 78, 16, 22 };

int main(void)
{
    print_numbers(items, LENGTH, false);
    quicksort(0, LENGTH - 1);
    print_numbers(items, LENGTH, true);
    return 0;
}

void quicksort(int low, int hi)
{
    if (low < hi) {
        int pivot = partition(low, hi);
        quicksort(low, pivot - 1);
        quicksort(pivot + 1, hi);
    }
}

int partition(int low, int hi)
{
    int pivot = items[hi];
    int i = low - 1;

    for (int j = low; j <= hi - 1; j++) {
        if (items[j] < pivot) {
            i++;
            int tmp = items[i];
            items[i] = items[j];
            items[j] = tmp;
        }
    }

    int tmp = items[i + 1];
    items[i + 1] = items[hi];
    items[hi] = tmp;

    return (i + 1);
}
