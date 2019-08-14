#include <string.h>
#include <stdbool.h>
#include "unittest.h"
#include "bstree.h"

char *test_create()
{
    return NULL;
}

int main()
{
    start_tests("bstree tests");
    run_test(test_create);
    end_tests();

    return 0;
}
