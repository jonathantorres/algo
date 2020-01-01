#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "unittest.h"
#include "ts_tree.h"

ts_tree *node = NULL;
char *value_a = "VALUEA";
char *value_b = "VALUEB";
char *value_2 = "VALUE2";
char *value_4 = "VALUE4";
char *reverse = "VALUER";
int traverse_count = 0;

char *test1 = "TEST";
char *test2 = "TEST2";
char *test3 = "TSET";
char *test4 = "T";

char *test_insert()
{
    node = ts_tree_insert(node, test1, strlen(test1), value_a);
    assert(node != NULL, "Failed to insert into tst.");

    node = ts_tree_insert(node, test2, strlen(test2), value_2);
    assert(node != NULL, "Failed to insert into tst with second name");

    node = ts_tree_insert(node, test3, strlen(test3), reverse);
    assert(node != NULL, "Failed to insert into tst with reverse name");

    node = ts_tree_insert(node, test4, strlen(test4), value_4);
    assert(node != NULL, "Failed to insert into tst with single letter");

    return NULL;
}

char *test_search_exact()
{
    // tst returns the last one inserted
    void *res = ts_tree_search(node, test1, strlen(test1));
    assert(res == value_a, "Got the wrong value back, should get A not B");

    // tst does not find if not exact
    res = ts_tree_search(node, "TESTNO", strlen("TESTNO"));
    assert(res == NULL, "Should not find anything");

    return NULL;
}

char *test_search_prefix()
{
    void *res = ts_tree_search_prefix(node, test1, strlen(test1));
    printf("result: %p, expected: %p\n", res, value_a);
    assert(res == value_a, "Got wrong value_a by prefix.");

    res = ts_tree_search_prefix(node, test1, 1);
    printf("result: %p, expected: %p\n", res, value_a);
    assert(res == value_4, "Got wrong value_4 for prefix of 1");

    res = ts_tree_search_prefix(node, "TE", strlen("TE"));
    assert(res != NULL, "Should find for short prefix.");

    res = ts_tree_search_prefix(node, "TE--", strlen("TE--"));
    assert(res != NULL, "Should find for partial prefix.");

    return NULL;
}

void ts_tree_traverse_test_cb(void *value, void *data)
{
    assert(value != NULL, "Should not get NULL value");
    assert(data == value_a, "Expecting value_a as the data");
    traverse_count++;
}

char *test_traverse()
{
    traverse_count = 0;
    ts_tree_traverse(node, ts_tree_traverse_test_cb, value_a);
    printf("traverse count is: %d\n", traverse_count);
    assert(traverse_count == 4, "Didn't find the 4 keys.");

    return NULL;
}

char *test_destroy()
{
    ts_tree_destroy(node);

    return NULL;
}

int main()
{
    start_tests("ts_tree tests");
    run_test(test_insert);
    run_test(test_search_exact);
    run_test(test_search_prefix);
    run_test(test_traverse);
    run_test(test_destroy);
    end_tests();

    return 0;
}
