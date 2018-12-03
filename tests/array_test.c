#include "unittest.h"
#include "array.h"
#include <stdio.h>

// utility method to print the contents of an array
// in this test we'll be using an array of strings
void array_print(array *_array)
{
    if (!_array) {
        fputs("Must provide an array.", stderr);
        exit(EXIT_FAILURE);
    }

    printf("[");

    // TODO

    printf("]\n");
}

char *test_create()
{
    array *_array = array_create(10, sizeof(int*));

    assert(_array->length == 0, "Array length should be 0");
    assert(_array->capacity == 10, "Array capacity should be 10");
    assert(_array->expand_rate == 100, "Array expand_rate should be 100");
    assert(_array->item_size == sizeof(int*), "Array item_size is not correct, it should be sizeof(int*)");
    assert(_array->contents != NULL, "Array contents should not be NULL");

    array_destroy(_array);

    return NULL;
}

char *test_destroy()
{
    array *_array = array_create(100, sizeof(int*));

    for (unsigned int i = 0; i < 100; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_push(_array, value);
        }
    }

    array_destroy(_array);

    return NULL;
}

char *test_clear()
{
    array *_array = array_create(100, sizeof(int*));

    for (unsigned int i = 0; i < 100; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_push(_array, value);
        }
    }

    array_clear(_array);
    assert(_array->capacity == 200, "Array capacity should be 200");
    assert(_array->length == 0, "Array length must be 0");
    assert(_array->contents != NULL, "Array contents should not be NULL");
    array_destroy(_array);

    return NULL;
}

char *test_push()
{
    array *_array = array_create(10, sizeof(int*));

    for (unsigned int i = 0; i < 100; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_push(_array, value);
        }
    }

    assert(_array->capacity == 110, "Array capacity should be 110");
    assert(_array->length == 100, "Array length should be 100");
    assert(_array->contents != NULL, "Array contents should not be NULL");

    array_destroy(_array);

    return NULL;
}

char *test_pop()
{
    array *_array = array_create(10, sizeof(int*));

    for (unsigned int i = 0; i < 5; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_push(_array, value);
        }
    }

    assert(_array->length == 5, "Array length should be 5");
    int *last_num = array_pop(_array);
    assert(*last_num == 20, "Last element's value should be 20");
    assert(_array->length == 4, "Array length should be 4");
    assert(_array->contents != NULL, "Array contents should not be NULL");
    array_destroy(_array);

    return NULL;
}

char *test_set()
{
    array *_array = array_create(10, sizeof(int*));

    for (unsigned int i = 0; i < 5; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_set(_array, value, i);
        }
    }

    assert(_array->capacity == 10, "Array capacity should be 10");
    assert(_array->length == 5, "Array length should be 5");
    assert(_array->contents != NULL, "Array contents should not be NULL");
    array_destroy(_array);

    return NULL;
}

char *test_get()
{
    array *_array = array_create(10, sizeof(int*));

    for (unsigned int i = 0; i < 5; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_push(_array, value);
        }
    }

    int *number = array_get(_array, 4);
    void *off_number = array_get(_array, 100);
    assert(*number == 20, "Element's value should be 20");
    assert(off_number == NULL, "The off number should be NULL");
    array_destroy(_array);

    return NULL;
}

char *test_remove()
{
    array *_array = array_create(10, sizeof(int*));

    for (unsigned int i = 0; i < 5; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_push(_array, value);
        }
    }

    assert(_array->length == 5, "Array length should be 5");
    int *number = array_remove(_array, 1);
    assert(*number == 5, "Element's value should be 5");
    assert(_array->length == 4, "Array length should be 4");
    array_destroy(_array);

    return NULL;
}

int main()
{
    start_tests("array tests");
    run_test(test_create);
    run_test(test_destroy);
    run_test(test_clear);
    run_test(test_push);
    run_test(test_pop);
    run_test(test_set);
    run_test(test_get);
    run_test(test_remove);
    end_tests();

    return 0;
}
