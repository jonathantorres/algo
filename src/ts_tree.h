#ifndef _ts_tree_h
#define _ts_tree_h

#include <stddef.h>

typedef struct ts_tree {
    char splitchar;
    struct ts_tree *low;
    struct ts_tree *equal;
    struct ts_tree *high;
    void *value;
} ts_tree;

void *ts_tree_search(ts_tree *root, const char *key, size_t len);
void *ts_tree_search_prefix(ts_tree *root, const char *key, size_t len);
typedef void (*ts_tree_traverse_cb)(void *value, void *data);
ts_tree *ts_tree_insert(ts_tree *node, const char *key, size_t len, void *value);
void ts_tree_traverse(ts_tree *node, ts_tree_traverse_cb cb, void *data);
void ts_tree_free(ts_tree *root);

#endif
