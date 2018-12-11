#include "unittest.h"
#include "cbuffer.h"

char *test_init()
{
    return NULL;
}

int main()
{
    start_tests("cbuffer tests");
    run_test(test_init);
    end_tests();

    return 0;
}
