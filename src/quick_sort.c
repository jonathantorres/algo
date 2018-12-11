#include "quick_sort.h"

void sort(array *_array, cmp_f cmp, unsigned int low, unsigned int hi);

unsigned int partition(array *_array, cmp_f cmp, unsigned int low, unsigned int hi)
{
    void *pivot = array_get(_array, hi);
    unsigned int i = low - 1;

    for (unsigned int j = low; j <= hi - 1; j++) {
        if (cmp(array_get(_array, j), pivot) < 0) {
            i++;
            void *tmp = array_get(_array, i);
            array_set(_array, array_get(_array, j), i);
            array_set(_array, tmp, j);
        }
    }

    void *tmp = array_get(_array, i + 1);
    array_set(_array, array_get(_array, hi), i + 1);
    array_set(_array, tmp, hi);

    return (i + 1);
}

void sort(array *_array, cmp_f cmp, unsigned int low, unsigned int hi)
{
    if (low < hi) {
        unsigned int pivot = partition(_array, cmp, low, hi);
        sort(_array, cmp, low, pivot - 1);
        sort(_array, cmp, pivot + 1, hi);
    }
}

void quick_sort(array *_array, cmp_f cmp)
{
    sort(_array, cmp, 0, _array->length - 1);
}
