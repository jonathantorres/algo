#ifndef _avl_tree_h
#define _avl_tree_h

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef int (*avl_tree_cmp)(void *a, void *b);

typedef struct avl_tree_node {
    struct avl_tree_node *parent;
    struct avl_tree_node *left;
    struct avl_tree_node *right;
    void *value;
} avl_tree_node;

typedef struct avl_tree {
    avl_tree_node *root;
    avl_tree_cmp cmp;
    int len;
} avl_tree;

typedef void (*avl_tree_cb)(avl_tree_node *node);

avl_tree *avl_tree_new(avl_tree_cmp cmp);
void avl_tree_insert(avl_tree *tree, void *value);
void avl_tree_delete(avl_tree *tree, void *value, avl_tree_cb cb);
void *avl_tree_search(avl_tree *tree, void *value);
void *avl_tree_find_max(avl_tree *tree);
void *avl_tree_find_min(avl_tree *tree);
void avl_tree_traverse(avl_tree *tree, avl_tree_cb cb);
void avl_tree_free(avl_tree *tree, avl_tree_cb cb);

#endif
