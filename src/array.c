#include "array.h"
#include <stdio.h>
#include <stdlib.h>

#define EXPAND_RATE 300

// creates a new empty array
array *array_create(unsigned int capacity, size_t item_size)
{
    array *_array = malloc(sizeof(array));

    if (!_array) {
        fputs("Not enough memory.", stderr);
        exit(EXIT_FAILURE);
    }

    _array->length = 0;
    _array->capacity = capacity;
    _array->expand_rate = EXPAND_RATE;
    _array->item_size = item_size;
    _array->contents = calloc(_array->capacity, _array->item_size);

    if (!_array->contents) {
        fputs("Not enough memory.", stderr);
        exit(EXIT_FAILURE);
    }

    return _array;
}

// empties and destroys the array completely
void array_destroy(array *_array)
{
    if (!_array) {
        fputs("Must provide an array.", stderr);
        exit(EXIT_FAILURE);
    }
}

// removes all the elements on the array, leaving it empty
void array_clear(array *_array)
{
    if (!_array) {
        fputs("Must provide an array.", stderr);
        exit(EXIT_FAILURE);
    }
}

// add element to the end
void array_push(array *_array, void *value)
{
    if (!_array) {
        fputs("Must provide an array.", stderr);
        exit(EXIT_FAILURE);
    }
}
