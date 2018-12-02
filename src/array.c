#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXPAND_RATE 100

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

    array_clear(_array);

    free(_array->contents);
    free(_array);
}

// removes all the elements on the array, leaving it empty
void array_clear(array *_array)
{
    if (!_array) {
        fputs("Must provide an array.", stderr);
        exit(EXIT_FAILURE);
    }

    unsigned int array_length = _array->length;

    for (unsigned int i = 0; i < array_length; i++) {
        if (_array->contents[i] != NULL) {
            free(_array->contents[i]);
        }
        _array->length--;
    }
}

// add element to the end
void array_push(array *_array, void *value)
{
    if (!_array) {
        fputs("Must provide an array.", stderr);
        exit(EXIT_FAILURE);
    }

    _array->contents[_array->length] = value;
    _array->length++;

    // expand if necessary
    if (_array->length >= _array->capacity) {
        int new_capacity = _array->capacity + EXPAND_RATE;
        void *contents = realloc(_array->contents, new_capacity * _array->item_size);

        if (!contents) {
            fputs("Not enough memory.", stderr);
            exit(EXIT_FAILURE);
        }

        _array->contents = contents;
        _array->capacity = new_capacity;
    }
}

// remove last element and return it
void *array_pop(array *_array)
{
    if (!_array) {
        fputs("Must provide an array.", stderr);
        exit(EXIT_FAILURE);
    }

    if (_array->length > 0) {
        unsigned int index = _array->length - 1;

        if (_array->contents[index] != NULL) {
            void *element = _array->contents[index];
            _array->contents[index] = NULL;
            _array->length--;

            return element;
        }
    }

    return NULL;
}

// add/set element at index
void array_set(array *_array, void *elem, unsigned int index)
{
    if (!_array) {
        fputs("Must provide an array.", stderr);
        exit(EXIT_FAILURE);
    }

    // index is too large
    if (index >= _array->length + 1) {
        return;
    }

    if (_array->contents[index] == NULL) {
        _array->length++;
    }

    _array->contents[index] = elem;
}

// get element at index
void *array_get(array *_array, unsigned int index)
{
    if (!_array) {
        fputs("Must provide an array.", stderr);
        exit(EXIT_FAILURE);
    }

    // index is too large
    if (index >= _array->length) {
        return NULL;
    }

    return _array->contents[index];
}
