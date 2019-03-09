#include "unittest.h"
#include "quick_sort.h"
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
    for (unsigned int i = 0; i < _array->length; i++) {
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

char *test_quick_sort()
{
    array *_array = array_create(10, sizeof(int*));

    for (unsigned int i = 0; i < 10; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = rand();
            array_push(_array, value);
        }
    }

    quick_sort(_array, cmp_int);
    // make sure it's sorted
    for (unsigned int i = 1; i < _array->length; i++) {
        void *val1 = array_get(_array, i - 1);
        void *val2 = array_get(_array, i);
        assert(cmp_int(val1, val2) < 0, "Array is not sorted");
    }

    array_destroy(_array);

    return NULL;
}

int main(void)
{
    start_tests("quick sort tests");
    run_test(test_quick_sort);
    end_tests();

    return 0;
}
