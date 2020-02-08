#include "unittest.h"
#include "heap_sort.h"

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

int gen_random_number()
{
    int lower = 1;
    int upper = 50;
    return (rand() % (upper - lower + 1)) + lower;
}

char *test_heap_sort()
{
    array *_array = array_new(10, sizeof(int*));

    for (unsigned int i = 0; i < 10; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = gen_random_number();
            array_push(_array, value);
        }
    }
    heap_sort(_array, cmp_int);

    // make sure it's sorted
    for (unsigned int i = 1; i < _array->len; i++) {
        void *a = array_get(_array, i - 1);
        void *b = array_get(_array, i);
        assert(cmp_int(a, b) <= 0, "Array is not sorted");
    }

    array_free(_array, NULL);

    return NULL;
}

int main(void)
{
    start_tests("heap sort tests");
    run_test(test_heap_sort);
    end_tests();

    return 0;
}
