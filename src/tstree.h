#ifndef _tstree_h
#define _tstree_h

#include <stddef.h>

typedef struct tstree {
    char splitchar;
    struct tstree *low;
    struct tstree *equal;
    struct tstree *high;
    void *value;
} tstree;

void *tstree_search(tstree *root, const char *key, size_t len);
void *tstree_search_prefix(tstree *root, const char *key, size_t len);
typedef void (*tstree_traverse_cb)(void *value, void *data);
tstree *tstree_insert(tstree *node, const char *key, size_t len, void *value);
void tstree_traverse(tstree *node, tstree_traverse_cb cb, void *data);
void tstree_destroy(tstree *root);

#endif
