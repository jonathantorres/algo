#ifndef _bs_tree_h
#define _bs_tree_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int (*bs_tree_compare) (void *a, void *b);

typedef struct bs_tree_node {
    void *key;
    void *value;
    struct bs_tree_node *left;
    struct bs_tree_node *right;
    struct bs_tree_node *parent;
} bs_tree_node;

typedef struct bs_tree {
    int count;
    bs_tree_compare compare;
    bs_tree_node *root;
} bs_tree;

typedef int (*bs_tree_traverse_cb) (bs_tree_node *node);

bs_tree *bs_tree_create(bs_tree_compare compare);
void bs_tree_destroy(bs_tree *tree);
int bs_tree_set(bs_tree *tree, void *key, void *value);
void *bs_tree_get(bs_tree *tree, void *key);
int bs_tree_traverse(bs_tree *tree, bs_tree_traverse_cb traverse_cb);
void *bs_tree_delete(bs_tree *tree, void *key);

#endif
