#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "binary_search.h"

void *binary_search(array *_array, void *key, cmp_f cmp)
{
    if (!_array) {
        fputs("[binary_search] Must provide an array.", stderr);
        return NULL;
    }

    unsigned int low = 0;
    unsigned int mid = 0;
    unsigned int high = _array->len - 1;
    void *guess = NULL;

    while (low <= high) {
        mid = (low + high) / 2;
        guess = array_get(_array, mid);
        if (cmp(guess, key) == 0) {
            return guess;
        } else if (cmp(guess, key) == 1) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return NULL;
}
