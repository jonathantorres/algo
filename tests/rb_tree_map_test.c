#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "unittest.h"
#include "rb_tree_map.h"

int tree_str_traverse_count = 0;

void rb_tree_map_str_free_cb(void *key, void *value)
{
    if (key) {
        // nothing to free here
    }
    if (value) {
        // nothing to free here
    }
}

void rb_tree_map_str_traverse_cb(void *key, void *value)
{
    tree_str_traverse_count++;
    // printf("key:%s - val:%s\n", (char*)key, (char*)value);
    if (key) {
        // nothing to do here
    }
    if (value) {
        // nothing to do here
    }
}

int rb_tree_map_str_cmp(void *a, void *b)
{
    return strcmp((char*)a, (char*)b);
}

char *test_new()
{
    rb_tree_map *tree = rb_tree_map_new(NULL);
    assert(tree != NULL, "Failed to create tree");
    return NULL;
}

char *test_free()
{
    rb_tree_map *tree = rb_tree_map_new(NULL);
    rb_tree_map_free(tree, rb_tree_map_str_free_cb);
    return NULL;
}

char *test_insert_strs()
{
    char *s1_k = "key1";
    char *s2_k = "key2";
    char *s3_k = "key3";
    char *s4_k = "key4";
    char *s1_v = "val1";
    char *s2_v = "val2";
    char *s3_v = "val3";
    char *s4_v = "val4";

    rb_tree_map *tree = rb_tree_map_new(rb_tree_map_str_cmp);
    rb_tree_map_insert(tree, s1_k, s1_v);
    rb_tree_map_insert(tree, s2_k, s2_v);
    assert(tree->len == 2, "Len of tree should be 2");
    rb_tree_map_insert(tree, s3_k, s3_v);
    rb_tree_map_insert(tree, s4_k, s4_v);
    assert(tree->len == 4, "Len of tree should be 4");
    rb_tree_map_free(tree, rb_tree_map_str_free_cb);
    return NULL;
}

char *test_insert_and_delete_strs()
{
    char *s1_k = "key1";
    char *s2_k = "key2";
    char *s3_k = "key3";
    char *s4_k = "key4";
    char *s5_k = "key5";
    char *s1_v = "val1";
    char *s2_v = "val2";
    char *s3_v = "val3";
    char *s5_v = "val5";

    rb_tree_map *tree = rb_tree_map_new(rb_tree_map_str_cmp);
    rb_tree_map_insert(tree, s1_k, s1_v);
    rb_tree_map_insert(tree, s2_k, s2_v);
    rb_tree_map_insert(tree, s3_k, s3_v);

    assert(tree->len == 3, "Len of tree should be 3");
    rb_tree_map_delete(tree, s2_k, rb_tree_map_str_free_cb);
    assert(tree->len == 2, "Len of tree should be 2");
    rb_tree_map_delete(tree, s1_k, rb_tree_map_str_free_cb);
    assert(tree->len == 1, "Len of tree should be 1");
    rb_tree_map_delete(tree, s4_k, rb_tree_map_str_free_cb);
    assert(tree->len == 1, "Len of tree should be 1");
    rb_tree_map_insert(tree, s5_k, s5_v);
    assert(tree->len == 2, "Len of tree should be 2");
    rb_tree_map_delete(tree, s5_k, rb_tree_map_str_free_cb);
    assert(tree->len == 1, "Len of tree should be 1");
    rb_tree_map_free(tree, rb_tree_map_str_free_cb);
    return NULL;
}

char *test_traverse()
{
    char *s1_k = "key1";
    char *s2_k = "key2";
    char *s3_k = "key3";
    char *s4_k = "key4";
    char *s1_v = "val1";
    char *s2_v = "val2";
    char *s3_v = "val3";
    char *s4_v = "val4";

    rb_tree_map *tree = rb_tree_map_new(rb_tree_map_str_cmp);
    rb_tree_map_insert(tree, s1_k, s1_v);
    rb_tree_map_insert(tree, s2_k, s2_v);
    rb_tree_map_insert(tree, s3_k, s3_v);
    rb_tree_map_insert(tree, s4_k, s4_v);

    assert(tree_str_traverse_count == 0, "Traverse count should be 0");
    rb_tree_map_traverse(tree, rb_tree_map_str_traverse_cb);
    assert(tree_str_traverse_count == 4, "Traverse count should be 4");
    return NULL;
}

int main()
{
    start_tests("rb_tree_map tests");
    run_test(test_new);
    run_test(test_free);
    run_test(test_insert_strs);
    run_test(test_insert_and_delete_strs);
    run_test(test_traverse);
    end_tests();

    return 0;
}
