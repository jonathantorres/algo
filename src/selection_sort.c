#include <stdio.h>
#include "selection_sort.h"

void selection_sort(array *_array, cmp_f cmp)
{
    if (!_array) {
        fputs("[selection_sort] Must provide an array.", stderr);
        return;
    }

    for (unsigned int j = 0; j < _array->length - 1; j++) {
        unsigned int min = j;
        for (unsigned int i = j + 1; i < _array->length; i++) {
            if (cmp(array_get(_array, i), array_get(_array, min)) < 0) {
                min = i;
            }
        }

        if (min != j) {
            void *tmp = array_get(_array, min);
            array_set(_array, array_get(_array, j), min);
            array_set(_array, tmp, j);
        }
    }
}
