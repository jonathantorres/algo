#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "unittest.h"
#include "bs_tree.h"

int tree_int_traverse_count = 0;

void bs_tree_int_free_cb(bs_tree_node *node)
{
    if (node) {
        // nothing to free here
    }
}

void bs_tree_int_traverse_cb(bs_tree_node *node)
{
    if (node) {
        tree_int_traverse_count++;
    }
    // printf("node val: %d\n", *(int *)node->value);
}

int bs_tree_int_cmp(void *a, void *b)
{
    if (*(int*)a < *(int*)b) {
        return -1;
    } else if (*(int*)a > *(int*)b) {
        return 1;
    } else {
        return 0;
    }
}

char *test_new()
{
    bs_tree *tree = bs_tree_new(NULL);
    assert(tree != NULL, "Failed to create tree");
    return NULL;
}

char *test_free()
{
    bs_tree *tree = bs_tree_new(NULL);
    bs_tree_free(tree, bs_tree_int_free_cb);
    return NULL;
}

char *test_insert_ints()
{
    int n1 = 10;
    int n2 = 3;
    int n3 = 43;
    int n4 = 12;

    bs_tree *tree = bs_tree_new(bs_tree_int_cmp);
    bs_tree_insert(tree, &n1);
    bs_tree_insert(tree, &n2);
    assert(tree->len == 2, "Len of tree should be 2");
    bs_tree_insert(tree, &n3);
    bs_tree_insert(tree, &n4);
    assert(tree->len == 4, "Len of tree should be 4");
    bs_tree_free(tree, bs_tree_int_free_cb);
    return NULL;
}

char *test_insert_and_delete_ints()
{
    int n1 = 100;
    int n2 = 323;
    int n3 = 431;
    int n4 = 9090;

    bs_tree *tree = bs_tree_new(bs_tree_int_cmp);
    bs_tree_insert(tree, &n1);
    bs_tree_insert(tree, &n2);
    bs_tree_insert(tree, &n3);

    assert(tree->len == 3, "Len of tree should be 3");
    bs_tree_delete(tree, &n2, bs_tree_int_free_cb);
    assert(tree->len == 2, "Len of tree should be 2");
    // bs_tree_delete(tree, &n1, bs_tree_int_free_cb); // fix segfault!
    // assert(tree->len == 1, "Len of tree should be 1");
    bs_tree_delete(tree, &n4, bs_tree_int_free_cb);
    // assert(tree->len == 1, "Len of tree should be 1");
    bs_tree_free(tree, bs_tree_int_free_cb);
    return NULL;
}

char *test_insert_strs()
{
    // TODO
    return NULL;
}

char *test_insert_and_delete_strs()
{
    // TODO
    return NULL;
}

char *test_traverse()
{
    int n1 = 100;
    int n2 = 323;
    int n3 = 431;
    int n4 = 9090;

    bs_tree *tree = bs_tree_new(bs_tree_int_cmp);
    bs_tree_insert(tree, &n1);
    bs_tree_insert(tree, &n2);
    bs_tree_insert(tree, &n3);
    bs_tree_insert(tree, &n4);

    assert(tree_int_traverse_count == 0, "Traverse count should be 0");
    bs_tree_traverse(tree, bs_tree_int_traverse_cb);
    assert(tree_int_traverse_count == 4, "Traverse count should be 4");
    return NULL;
}

int main()
{
    start_tests("bs_tree tests");
    run_test(test_new);
    run_test(test_free);
    run_test(test_insert_ints);
    run_test(test_insert_and_delete_ints);
    run_test(test_traverse);
    end_tests();

    return 0;
}
