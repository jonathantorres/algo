#include "unittest.h"
#include "htable.h"

char *test_create()
{
    return NULL;
}

int main()
{
    start_tests("hash table tests");
    run_test(test_create);
    end_tests();

    return 0;
}
