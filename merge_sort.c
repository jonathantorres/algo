#include "print_numbers.h"
#include <stdlib.h>

void merge_sort(int array[], int length, int left, int right);
void merge(int array[], int left, int right, int length);

#define LENGTH 10
int items[LENGTH] = { 4, 9, 3, 11, 55, 4, 12, 78, 16, 22 };

int main(void)
{
    print_numbers(items, LENGTH, false);
    merge_sort(items, LENGTH, 0, LENGTH - 1);
    print_numbers(items, LENGTH, true);
    return 0;
}

void merge_sort(int array[], int length, int left, int right)
{
    if (right - left == 1) {
        if (array[left] > array[right]) {
            int tmp = array[left];
            items[left] = items[right];
            items[right] = tmp;
        }
    } else if (left == right) {
        //
    } else {
        merge_sort(array, length, left, (left + right) / 2);
        merge_sort(array, length, ((left + right) / 2) + 1, right);
        merge(array, left, right, length);
    }
}

void merge(int array[], int left, int right, int length)
{
    int *cpy = (int*) malloc(length * sizeof(int));
    int counter = left;
    int p1, p2;

    p1 = left;
    p2 = ((left + right) / 2) + 1;

    while ((p1 < ((left + right) / 2) + 1) && (p2 < right + 1)) {
        if (array[p1] <= array[p2]) {
            cpy[counter++] = array[p1];
            p1++;
        } else {
            cpy[counter++] = array[p2];
            p2++;
        }
    }

    if (p2 == right + 1) {
        while ((p1 < ((left + right) / 2) + 1)) {
            cpy[counter++] = array[p1];
            p1++;
        }
    } else {
        while ((p2 < right + 1)) {
            cpy[counter++] = array[p2];
            p2++;
        }
    }

    for (int counter = left; counter < right - left + 1; counter++) {
        array[counter] = cpy[counter];
    }
}
