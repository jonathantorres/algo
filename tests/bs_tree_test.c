#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "unittest.h"
#include "bs_tree.h"

int tree_int_traverse_count = 0;

void bs_tree_int_traverse_cb(void *value)
{
    if (value) {
        tree_int_traverse_count++;
    }
    // printf("value: %d\n", *(int *)value);
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

int bs_tree_str_cmp(void *a, void *b)
{
    return strcmp((char*)a, (char*)b);
}

char *test_new()
{
    bs_tree *tree = bs_tree_new(NULL);
    assert(tree != NULL, "Failed to create tree");
    bs_tree_free(tree, NULL);
    return NULL;
}

char *test_free()
{
    bs_tree *tree = bs_tree_new(NULL);
    bs_tree_free(tree, NULL);
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
    bs_tree_free(tree, NULL);
    return NULL;
}

char *test_insert_and_delete_ints()
{
    int n1 = 100;
    int n2 = 323;
    int n3 = 431;
    int n4 = 9090;
    int n5 = 8080;

    bs_tree *tree = bs_tree_new(bs_tree_int_cmp);
    bs_tree_insert(tree, &n1);
    bs_tree_insert(tree, &n2);
    bs_tree_insert(tree, &n3);

    assert(tree->len == 3, "Len of tree should be 3");
    bs_tree_delete(tree, &n2, NULL);
    assert(tree->len == 2, "Len of tree should be 2");
    bs_tree_delete(tree, &n1, NULL);
    assert(tree->len == 1, "Len of tree should be 1");
    bs_tree_delete(tree, &n4, NULL);
    assert(tree->len == 1, "Len of tree should be 1");
    bs_tree_insert(tree, &n5);
    assert(tree->len == 2, "Len of tree should be 2");
    bs_tree_delete(tree, &n5, NULL);
    assert(tree->len == 1, "Len of tree should be 1");
    bs_tree_free(tree, NULL);
    return NULL;
}

char *test_insert_strs()
{
    char *str1 = "Jonathan";
    char *str2 = "Torres";
    char *str3 = "This is another string";
    char *str4 = "And a fourth string";

    bs_tree *tree = bs_tree_new(bs_tree_str_cmp);
    bs_tree_insert(tree, &str1);
    bs_tree_insert(tree, &str2);
    bs_tree_insert(tree, &str3);
    assert(tree->len == 3, "Len of tree should be 3");
    bs_tree_insert(tree, &str4);
    assert(tree->len == 4, "Len of tree should be 4");
    bs_tree_free(tree, NULL);
    return NULL;
}

char *test_insert_and_delete_strs()
{
    char *str1 = "Jonathan";
    char *str2 = "Torres";
    char *str3 = "This is another string";
    char *str4 = "And a fourth string";

    bs_tree *tree = bs_tree_new(bs_tree_str_cmp);
    bs_tree_insert(tree, &str1);
    bs_tree_insert(tree, &str2);
    bs_tree_insert(tree, &str3);
    assert(tree->len == 3, "Len of tree should be 3");
    bs_tree_delete(tree, &str1, NULL);
    assert(tree->len == 2, "Len of tree should be 2");
    bs_tree_insert(tree, &str4);
    assert(tree->len == 3, "Len of tree should be 3");
    bs_tree_delete(tree, &str2, NULL);
    bs_tree_delete(tree, &str3, NULL);
    assert(tree->len == 1, "Len of tree should be 1");
    bs_tree_free(tree, NULL);
    return NULL;
}

char *test_traverse()
{
    int n1 = 100;
    int n2 = 323;
    int n3 = 431;
    int n4 = 9090;

    tree_int_traverse_count = 0;

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

char *test_deletion()
{
    int n1 = 1;
    int n2 = 2;
    int n3 = 3;
    int n4 = 4;
    int n5 = 5;
    int n6 = 6;
    int n7 = 7;
    int n8 = 8;
    int n9 = 9;
    int n10 = 10;
    int n11 = 11;
    int n12 = 12;

    bs_tree *tree = bs_tree_new(bs_tree_int_cmp);
    bs_tree_insert(tree, &n4);
    bs_tree_insert(tree, &n2);
    bs_tree_insert(tree, &n8);
    bs_tree_insert(tree, &n1);
    bs_tree_insert(tree, &n3);
    bs_tree_insert(tree, &n6);
    bs_tree_insert(tree, &n12);
    bs_tree_insert(tree, &n5);
    bs_tree_insert(tree, &n7);
    bs_tree_insert(tree, &n11);
    bs_tree_insert(tree, &n9);
    bs_tree_insert(tree, &n10);

    assert(tree->len == 12, "Len of tree should be 12");
    bs_tree_delete(tree, &n7, NULL);
    assert(tree->len == 11, "Len of tree should be 11");
    bs_tree_delete(tree, &n6, NULL);
    assert(tree->len == 10, "Len of tree should be 10");
    bs_tree_delete(tree, &n8, NULL);
    assert(tree->len == 9, "Len of tree should be 9");
    bs_tree_free(tree, NULL);
    return NULL;
}

int main()
{
    start_tests("bs_tree tests");
    run_test(test_new);
    run_test(test_free);
    run_test(test_insert_ints);
    run_test(test_insert_strs);
    run_test(test_deletion);
    run_test(test_insert_and_delete_ints);
    run_test(test_insert_and_delete_strs);
    run_test(test_traverse);
    end_tests();

    return 0;
}
