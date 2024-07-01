#ifndef _rb_tree_map_h
#define _rb_tree_map_h

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef int (*rb_tree_map_cmp)(void *a, void *b);
typedef void (*rb_tree_map_cb)(void *key, void *value);

typedef enum rb_tree_map_color {
    RB_TREE_MAP_RED,
    RB_TREE_MAP_BLACK
} rb_tree_map_color;

typedef struct rb_tree_map_node {
    struct rb_tree_map_node *parent;
    struct rb_tree_map_node *left;
    struct rb_tree_map_node *right;
    rb_tree_map_color color;
    void *key;
    void *value;
} rb_tree_map_node;

typedef struct rb_tree_map {
    rb_tree_map_node *root;
    rb_tree_map_node *sentinel;
    rb_tree_map_cmp cmp;
    int len;
} rb_tree_map;

#define rb_tree_map_red(node) (node)->color = RB_TREE_MAP_RED
#define rb_tree_map_black(node) (node)->color = RB_TREE_MAP_BLACK
#define rb_tree_map_is_red(node) (node)->color == RB_TREE_MAP_RED
#define rb_tree_map_is_black(node) (node)->color == RB_TREE_MAP_BLACK

rb_tree_map *rb_tree_map_new(rb_tree_map_cmp cmp);
void rb_tree_map_insert(rb_tree_map *tree, void *key, void *value);
void rb_tree_map_delete(rb_tree_map *tree, void *key, rb_tree_map_cb cb);
void *rb_tree_map_search(rb_tree_map *tree, void *key);
void *rb_tree_map_find_max(rb_tree_map *tree);
void *rb_tree_map_find_min(rb_tree_map *tree);
void rb_tree_map_traverse(rb_tree_map *tree, rb_tree_map_cb cb);
void rb_tree_map_free(rb_tree_map *tree, rb_tree_map_cb cb);

#endif
