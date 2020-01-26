#include "unittest.h"
#include "binary_search.h"
#include <stdlib.h>

// utility method to print the contents of an array
// in this test we'll be using an array of numbers
void array_print(array *_array, char type)
{
    if (!_array) {
        fputs("Must provide an array.", stderr);
        exit(EXIT_FAILURE);
    }

    printf("[");
    for (unsigned int i = 0; i < _array->len; i++) {
        void *val = NULL;
        switch (type) {
            case 'i':
                val = (int*)array_get(_array, i);
                printf("%d,", *(int*)val);
            break;

            case 's':
                val = array_get(_array, i);
                printf("%s,", (char*)val);
            break;
        }
    }
    printf("]\n");
}

int cmp_int(void *a, void *b)
{
    if (*(int*)a > *(int*)b) {
        return 1;
    } else if (*(int*)a < *(int*)b) {
        return -1;
    } else {
        return 0;
    }
}

char *test_binary_search_found()
{
    array *_array = array_new(10, sizeof(int*));

    for (int i = 1; i <= 10; i++) {
        int *val = malloc(sizeof(int));
        *val = i * 10;
        array_push(_array, val);
    }

    int search_for = 30;
    void *found = binary_search(_array, &search_for, cmp_int);

    assert(*(int*)found == 30, "The found item should have been the number 30");
    assert(found != NULL, "The found item should not be NULL");
    array_free(_array);

    return NULL;
}

char *test_binary_search_not_found()
{
    array *_array = array_new(10, sizeof(int*));

    for (int i = 1; i <= 10; i++) {
        int *val = malloc(sizeof(int));
        *val = i * 10;
        array_push(_array, val);
    }

    int search_for = 150;
    void *found = binary_search(_array, &search_for, cmp_int);

    assert(found == NULL, "The found item should be NULL");
    array_free(_array);

    return NULL;
}

int main(void)
{
    start_tests("binary search tests");
    run_test(test_binary_search_found);
    run_test(test_binary_search_not_found);
    end_tests();

    return 0;
}
