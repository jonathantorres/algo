#ifndef _trie_h
#define _trie_h

#include "array.h"
#include <stdbool.h>

typedef int (*trie_compare)(void *a, void *b);

typedef struct trie_node {
    void *value;
    array *paths;
} trie_node;

typedef struct trie {
    trie_node *root;
    trie_compare cmp;
} trie;

typedef bool (*trie_traverse_cb)(trie_node *node);

void *trie_create(trie_compare cmp);
void trie_destroy(trie *_trie);
bool trie_insert(trie *_trie, void *key, void *value);
void *trie_get(trie *_trie, void *key);
bool trie_traverse(trie *_trie, trie_traverse_cb cb);

#endif
