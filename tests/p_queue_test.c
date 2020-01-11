#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "unittest.h"
#include "p_queue.h"

char *test_new()
{
    return NULL;
}

char *test_free()
{
    return NULL;
}

int main()
{
    start_tests("p_queue tests");
    run_test(test_new);
    run_test(test_free);
    end_tests();

    return 0;
}
