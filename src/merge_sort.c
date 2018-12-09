#include "merge_sort.h"

void split_merge(array *copy, unsigned int begin, unsigned int end, array *_array, cmp_f cmp);

void *copy_array(array *_array)
{
    array *copy = array_create(_array->length, _array->item_size);

    for (unsigned int i = 0; i < _array->length; i++) {
        array_push(copy, array_get(_array, i));
    }

    return copy;
}

void merge(array *copy, unsigned int begin, unsigned int middle, unsigned int end, array *_array, cmp_f cmp)
{
    unsigned int i = begin;
    unsigned int j = middle;

    for (unsigned int k = begin; k < end; k++) {
        if (i < middle && (j >= end || cmp(array_get(copy, i), array_get(copy, j)) <= 0)) {
            array_set(_array, array_get(copy, i), k);
            i = i + 1;
        } else {
            array_set(_array, array_get(copy, j), k);
            j = j + 1;
        }
    }
}

void split_merge(array *copy, unsigned int begin, unsigned int end, array *_array, cmp_f cmp)
{
    if (end - begin < 2) {
        return;
    }

    unsigned int middle = (end + begin) / 2;
    split_merge(_array, begin, middle, copy, cmp);
    split_merge(_array, middle, end, copy, cmp);
    merge(copy, begin, middle, end, _array, cmp);
}

void merge_sort(array *_array, cmp_f cmp)
{
    array *copy = copy_array(_array);
    split_merge(copy, 0, _array->length, _array, cmp);
}
