#include <stdio.h>
#include <stdlib.h>
#include "bubble_sort.h"

void bubble_sort(array *_array, cmp_f cmp)
{
    if (!_array) {
        fputs("[bubble_sort] Must provide an array.", stderr);
        exit(EXIT_FAILURE);
    }

    int swapped = 0;
    if (_array->length > 1) {
        do {
            swapped = 0;
            for (unsigned int i = 1; i < _array->length; i++) {
                if (cmp(array_get(_array, i - 1), array_get(_array, i)) > 0) {
                    void *tmp = array_get(_array, i);
                    array_set(_array, array_get(_array, i - 1), i);
                    array_set(_array, tmp, i - 1);
                    swapped = 1;
                }
            }
        } while (swapped == 1);
    }
}
