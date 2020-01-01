#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "unittest.h"
#include "bs_tree.h"

static int traverse_called = 0;
char *test1 = "test data 1";
char *test2 = "test data 2";
char *test3 = "test data 3";
char *expect1 = "THE VALUE 1";
char *expect2 = "THE VALUE 2";
char *expect3 = "THE VALUE 3";

static int traverse_good_cb(bs_tree_node *node)
{
    printf("KEY: %s\n", (char*)node->key);
    traverse_called++;
    return 0;
}

static int traverse_fail_cb(bs_tree_node *node)
{
    printf("KEY: %s\n", (char*)node->key);
    traverse_called++;

    if (traverse_called == 2) {
        return 1;
    } else {
        return 0;
    }
}

char *test_create()
{
    bs_tree *tree = bs_tree_create(NULL);
    assert(tree != NULL, "Failed to create tree");
    return NULL;
}

char *test_destroy()
{
    bs_tree *tree = bs_tree_create(NULL);
    bs_tree_destroy(tree);
    return NULL;
}

char *test_get_set()
{
    bs_tree *tree = bs_tree_create(NULL);

    int rc = bs_tree_set(tree, test1, expect1);
    assert(rc == 0, "Failed to set test1");
    char *result = bs_tree_get(tree, test1);
    assert(result == expect1, "Wrong value for test1");

    rc = bs_tree_set(tree, test2, expect2);
    assert(rc == 0, "Failed to set test2");
    result = bs_tree_get(tree, test2);
    assert(result == expect2, "Wrong value for test2");

    rc = bs_tree_set(tree, test3, expect3);
    assert(rc == 0, "Failed to set test3");
    result = bs_tree_get(tree, test3);
    assert(result == expect3, "Wrong value for test3");

    return NULL;
}

char *test_traverse()
{
    bs_tree *tree = bs_tree_create(NULL);
    bs_tree_set(tree, test1, expect1);
    bs_tree_set(tree, test2, expect2);
    bs_tree_set(tree, test3, expect3);

    int rc = bs_tree_traverse(tree, traverse_good_cb);
    assert(rc == 0, "Failed to traverse");
    assert(traverse_called == 3, "Wrong traverse count");

    traverse_called = 0;
    rc = bs_tree_traverse(tree, traverse_fail_cb);
    assert(rc == 1, "Failed to traverse");
    assert(traverse_called == 2, "Wrong count traverse for fail");

    return NULL;
}

char *test_delete()
{
    bs_tree *tree = bs_tree_create(NULL);
    bs_tree_set(tree, test1, expect1);
    bs_tree_set(tree, test2, expect2);
    bs_tree_set(tree, test3, expect3);

    char *deleted = (char*) bs_tree_delete(tree, test1);
    assert(deleted != NULL, "Got NULL on delete");
    assert(deleted == expect1, "Should get test1");
    char *result = bs_tree_get(tree, test1);
    assert(result == NULL, "Should delete");

    deleted = (char*) bs_tree_delete(tree, test1);
    assert(deleted == NULL, "Should get NULL on delete");

    deleted = (char*) bs_tree_delete(tree, test2);
    assert(deleted != NULL, "Got NULL on delete");
    assert(deleted == expect2, "Should get test2");
    result = bs_tree_get(tree, test2);
    assert(result == NULL, "Should delete");

    deleted = (char*) bs_tree_delete(tree, test3);
    assert(deleted != NULL, "Got NULL on delete");
    assert(deleted == expect3, "Should get test3");
    result = bs_tree_get(tree, test3);
    assert(result == NULL, "Should delete");

    // test deleting non-existing stuff
    deleted = (char*) bs_tree_delete(tree, test3);
    assert(deleted == NULL, "Should get NULL");

    return NULL;
}

char *test_fuzzing()
{
    return NULL;
}

int main()
{
    start_tests("bs_tree tests");
    run_test(test_create);
    run_test(test_destroy);
    run_test(test_get_set);
    run_test(test_traverse);
    run_test(test_delete);
    run_test(test_fuzzing);
    end_tests();

    return 0;
}
