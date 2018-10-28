#include <stdio.h>
#include "unittest.h"
#include "calc.h"

char *test_add_nums()
{
    assert(add_nums(1, 1) == 2, "1 + 1 does not equal 2");
    assert(add_nums(1, 3) == 4, "1 + 3 does not equal 4");

    return NULL;
}

int main()
{
    start_tests("calculator tests");
    run_test(test_add_nums);
    end_tests();

    return 0;
}
