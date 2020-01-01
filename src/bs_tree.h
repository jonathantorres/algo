#ifndef _bs_tree_h
#define _bs_tree_h

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef int (*bs_tree_cmp)(void *a, void *b);

typedef struct bs_tree_node {
    struct bs_tree_node *parent;
    struct bs_tree_node *left;
    struct bs_tree_node *right;
    void *value;
} bs_tree_node;

typedef struct bs_tree {
    bs_tree_node *root;
    bs_tree_cmp cmp;
    int len;
} bs_tree;

typedef void (*bs_tree_cb)(bs_tree_node *node);

bs_tree *bs_tree_new(bs_tree_cmp cmp);
void bs_tree_insert(bs_tree *tree, void *value);
void bs_tree_delete(bs_tree *tree, void *value, bs_tree_cb cb);
void *bs_tree_search(bs_tree *tree, void *value);
void *bs_tree_find_max(bs_tree *tree);
void *bs_tree_find_min(bs_tree *tree);
void bs_tree_traverse(bs_tree *tree, bs_tree_cb cb);
void bs_tree_free(bs_tree *tree, bs_tree_cb cb);

#endif
