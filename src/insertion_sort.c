#include <stdio.h>
#include "insertion_sort.h"

void insertion_sort(array *_array, cmp_f cmp)
{
    if (!_array) {
        fputs("Must provide an array.", stderr);
        exit(EXIT_FAILURE);
    }

    unsigned int i = 1;
    while (i < _array->length) {
        unsigned int j = i;
        while (j > 0 && cmp(array_get(_array, j - 1), array_get(_array, j)) > 0) {
            void *tmp = array_get(_array, j);
            array_set(_array, array_get(_array, j - 1), j);
            array_set(_array, tmp, j - 1);
            j--;
        }
        i++;
    }
}
