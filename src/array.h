#ifndef _array_h
#define _array_h

#include <stdlib.h>

typedef struct array {
    unsigned int length;
    unsigned int capacity;
    unsigned int expand_rate;
    size_t item_size;
    void **contents;
} array;

// creates a new empty array
array *array_create(unsigned int capacity, size_t item_size);

// empties and destroys the array completely
void array_destroy(array *_array);

// removes all the elements on the array, leaving it empty
void array_clear(array *_array);

// add element to the end
void array_push(array *_array, void *value);

// remove last element and return it
void *array_pop(array *_array);

// add/set element at index
void array_set(array *_array, void *elem, unsigned int index);

// get element at index
void *array_get(array *_array, unsigned int index);

// remove element at index and return it
void *array_remove(array *_array, int index);

// TODO: function to print contents
// TODO: function to sort contents

// add element to the beginning
void array_shift(array *_array, void *value);

// remove first element and return it
void *array_unshift(array *_array);

#endif
