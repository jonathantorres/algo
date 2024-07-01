#ifndef _rb_tree_h
#define _rb_tree_h

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef int (*rb_tree_cmp)(void *a, void *b);
typedef void (*rb_tree_cb)(void *value);

typedef enum rb_tree_color {
    RB_TREE_RED,
    RB_TREE_BLACK
} rb_tree_color;

typedef struct rb_tree_node {
    struct rb_tree_node *parent;
    struct rb_tree_node *left;
    struct rb_tree_node *right;
    rb_tree_color color;
    void *value;
} rb_tree_node;

typedef struct rb_tree {
    rb_tree_node *root;
    rb_tree_node *sentinel;
    rb_tree_cmp cmp;
    int len;
} rb_tree;

#define rb_tree_red(node) (node)->color = RB_TREE_RED
#define rb_tree_black(node) (node)->color = RB_TREE_BLACK
#define rb_tree_is_red(node) (node)->color == RB_TREE_RED
#define rb_tree_is_black(node) (node)->color == RB_TREE_BLACK

rb_tree *rb_tree_new(rb_tree_cmp cmp);
void rb_tree_insert(rb_tree *tree, void *value);
void rb_tree_delete(rb_tree *tree, void *value, rb_tree_cb cb);
void *rb_tree_search(rb_tree *tree, void *value);
void *rb_tree_find_max(rb_tree *tree);
void *rb_tree_find_min(rb_tree *tree);
void rb_tree_traverse(rb_tree *tree, rb_tree_cb cb);
void rb_tree_free(rb_tree *tree, rb_tree_cb cb);

#endif
