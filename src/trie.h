#ifndef _trie_h
#define _trie_h

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

typedef int (*trie_cmp)(void *a, void *b);

typedef struct trie_node {
    void *value;
    array *paths;
} trie_node;

typedef struct trie {
    trie_node *root;
    trie_cmp cmp;
} trie;

typedef void (*trie_cb)(trie_node *node);

trie *trie_new(trie_cmp cmp);
void trie_free(trie *_trie, trie_cb cb);
bool trie_insert(trie *_trie, char *key, void *value);
void *trie_get(trie *_trie, char *key);
void trie_traverse(trie *_trie, trie_cb cb);

#endif
