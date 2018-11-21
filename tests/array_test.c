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

char *test_run()
{
    return NULL;
}

int main()
{
    start_tests("array tests");
    run_test(test_run);
    end_tests();

    return 0;
}
