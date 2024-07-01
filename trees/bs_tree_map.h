#ifndef _bs_tree_map_h
#define _bs_tree_map_h

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef int (*bs_tree_map_cmp)(void *a, void *b);
typedef void (*bs_tree_map_cb)(void *key, void *value);

typedef struct bs_tree_map_node {
    struct bs_tree_map_node *parent;
    struct bs_tree_map_node *left;
    struct bs_tree_map_node *right;
    void *key;
    void *value;
} bs_tree_map_node;

typedef struct bs_tree_map {
    bs_tree_map_node *root;
    bs_tree_map_cmp cmp;
    int len;
} bs_tree_map;


bs_tree_map *bs_tree_map_new(bs_tree_map_cmp cmp);
void bs_tree_map_insert(bs_tree_map *tree, void *key, void *value);
void bs_tree_map_delete(bs_tree_map *tree, void *key, bs_tree_map_cb cb);
void *bs_tree_map_search(bs_tree_map *tree, void *key);
void *bs_tree_map_find_max(bs_tree_map *tree);
void *bs_tree_map_find_min(bs_tree_map *tree);
void bs_tree_map_traverse(bs_tree_map *tree, bs_tree_map_cb cb);
void bs_tree_map_free(bs_tree_map *tree, bs_tree_map_cb cb);

#endif
