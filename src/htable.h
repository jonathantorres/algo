#ifndef _htable_h
#define _htable_h

#include "array.h"
#include <stdbool.h>

#define NUM_OF_BUCKETS 100

typedef int (*htable_compare)(void *a, void *b);

typedef struct htable {
    array *buckets;
    htable_compare cmp;
} htable;

typedef struct htable_node {
    void *key;
    void *value;
    size_t hash;
} htable_node;

typedef bool (*htable_node_cb)(htable_node *node);

htable *htable_create(htable_compare cmp);
void htable_destroy(htable *_htable);
void *htable_get(htable *_htable, void *key);
bool htable_set(htable *_htable, void *key, void *value);
void *htable_remove(htable *_htable, void *key);
bool htable_traverse(htable *_htable, htable_node_cb cb);

#endif
