#include "unittest.h"
#include "avl_tree.h"

char *test_new()
{
    return NULL;
}

int main(void)
{
    start_tests("avl_tree tests");
    run_test(test_new);
    // run_test(test_free);
    // run_test(test_insert_ints);
    // run_test(test_insert_strs);
    // run_test(test_insert_and_delete_ints);
    // run_test(test_insert_and_delete_strs);
    // run_test(test_traverse);
    end_tests();
    return 0;
}
