#include "array.h"

#define EXPAND_RATE 100

void *_array_remove_element_at(array *_array, unsigned int index)
{
    if (_array->contents[index] != NULL) {
        void *element = _array->contents[index];
        _array->contents[index] = NULL;
        _array->len--;

        return element;
    }

    return NULL;
}

// creates a new empty array
array *array_new(unsigned int capacity, size_t item_size)
{
    array *_array = malloc(sizeof(array));

    if (!_array) {
        return NULL;
    }

    _array->len = 0;
    _array->capacity = capacity;
    _array->expand_rate = EXPAND_RATE;
    _array->item_size = item_size;
    _array->contents = calloc(_array->capacity, _array->item_size);

    if (!_array->contents) {
        return NULL;
    }

    return _array;
}

// empties and frees the array completely
void array_free(array *_array, array_free_cb cb)
{
    if (!_array) {
        return;
    }

    array_clear(_array, cb);
    free(_array->contents);
    free(_array);
}

// removes all the elements on the array, leaving it empty
void array_clear(array *_array, array_free_cb cb)
{
    if (!_array) {
        return;
    }

    unsigned int array_len = _array->len;

    for (unsigned int i = 0; i < array_len; i++) {
        if (_array->contents[i]) {
            if (cb) {
                cb(_array->contents[i]);
            }
            _array->contents[i] = NULL;
        }
        _array->len--;
    }
}

void array_expand(array *_array)
{
    int new_capacity = _array->capacity + EXPAND_RATE;
    void *contents = realloc(_array->contents, new_capacity * _array->item_size);

    if (!contents) {
        return;
    }

    _array->contents = contents;
    _array->capacity = new_capacity;
}

// add element to the end
void array_push(array *_array, void *value)
{
    if (!_array) {
        return;
    }

    _array->contents[_array->len] = value;
    _array->len++;

    // expand if necessary
    if (_array->len >= _array->capacity) {
        array_expand(_array);
    }
}

// remove last element and return it
void *array_pop(array *_array)
{
    if (!_array) {
        return NULL;
    }

    void *element = NULL;
    if (_array->len > 0) {
        element = _array_remove_element_at(_array, _array->len - 1);
    }

    return element;
}

// add/set element at index
void array_set(array *_array, void *elem, unsigned int index)
{
    if (!_array) {
        return;
    }

    // index is too large
    if (index >= _array->capacity) {
        return;
    }
    if (index >= _array->len) {
        _array->len = index + 1;
    }

    _array->contents[index] = elem;
}

// get element at index
void *array_get(array *_array, unsigned int index)
{
    if (!_array) {
        return NULL;
    }

    // index is too large
    if (index >= _array->len) {
        return NULL;
    }

    return _array->contents[index];
}

// remove element at index and return it
void *array_remove(array *_array, unsigned int index)
{
    if (!_array) {
        return NULL;
    }

    // index is too large
    if (index >= _array->len) {
        return NULL;
    }

    void *element = _array_remove_element_at(_array, index);

    if (element != NULL && _array->contents[index + 1] != NULL) {
        memmove(
            &_array->contents[index],
            &_array->contents[index + 1],
            sizeof(_array->item_size) * (_array->len - index)
        );
    }

    return element;
}

// add element to the beginning
void array_shift(array *_array, void *value)
{
    if (!_array) {
        return;
    }

    if (_array->len > 0) {
        memmove(
            &_array->contents[1],
            _array->contents,
            sizeof(_array->item_size) * _array->len
        );
    }

    _array->contents[0] = value;
    _array->len++;

    // expand if necessary
    if (_array->len >= _array->capacity) {
        array_expand(_array);
    }
}

// remove first element and return it
void *array_unshift(array *_array)
{
    if (!_array) {
        return NULL;
    }

    void *element = NULL;
    if (_array->len > 0) {
        element = _array_remove_element_at(_array, 0);

        memmove(
            _array->contents,
            &_array->contents[1],
            sizeof(_array->item_size) * _array->len
        );
    }

    return element;
}

void array_swap(array *_array, unsigned int a, unsigned int b)
{
    if (!_array) {
        return;
    }
    if (a == b) {
        return;
    }
    if (a > _array->len-1 || b > _array->len-1) {
        return;
    }

    void *a_tmp = array_get(_array, a);
    void *b_tmp = array_get(_array, b);
    if (!a_tmp || !b_tmp) {
        return;
    }
    array_set(_array, b_tmp, a);
    array_set(_array, a_tmp, b);
}
