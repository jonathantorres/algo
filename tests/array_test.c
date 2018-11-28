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
    array *_array = array_create(10, sizeof(int));

    assert(_array->length == 0, "Array length should be 0");
    assert(_array->capacity == 10, "Array capacity should be 100");
    assert(_array->expand_rate == 300, "Array expand_rate should be 300");
    assert(_array->item_size == sizeof(int), "Array item_size is not correct, it should be sizeof(int)");
    assert(_array->contents != NULL, "Array contents should not be NULL");

    return NULL;
}

int main()
{
    start_tests("array tests");
    run_test(test_create);
    end_tests();

    return 0;
}
