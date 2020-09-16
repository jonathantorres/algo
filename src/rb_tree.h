#ifndef _rb_tree_h
#define _rb_tree_h

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef int (*rb_tree_cmp)(void *a, void *b);

typedef struct rb_tree_node {
    struct rb_tree_node *parent;
    struct rb_tree_node *left;
    struct rb_tree_node *right;
    void *value;
} rb_tree_node;

typedef struct rb_tree {
    rb_tree_node *root;
    rb_tree_cmp cmp;
    int len;
} rb_tree;

typedef void (*rb_tree_cb)(rb_tree_node *node);

rb_tree *rb_tree_new(rb_tree_cmp cmp);
void rb_tree_insert(rb_tree *tree, void *value);
void rb_tree_delete(rb_tree *tree, void *value, rb_tree_cb cb);
void *rb_tree_search(rb_tree *tree, void *value);
void *rb_tree_find_max(rb_tree *tree);
void *rb_tree_find_min(rb_tree *tree);
void rb_tree_traverse(rb_tree *tree, rb_tree_cb cb);
void rb_tree_free(rb_tree *tree, rb_tree_cb cb);

#endif
