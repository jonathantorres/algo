#include "unittest.h"
#include "bubble_sort.h"

char *test_bubble_sort()
{
    bubble_sort(NULL, NULL);
    return NULL;
}

int main(void)
{
    start_tests("bubble sort tests");
    run_test(test_bubble_sort);
    end_tests();

    return 0;
}
