#ifndef _h_table_h
#define _h_table_h

#include "array.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef int (*h_table_cmp)(void *a, void *b);
typedef void (*h_table_cb)(void *key, void *value);

typedef struct h_table {
    array *buckets;
    h_table_cmp cmp;
} h_table;

typedef struct h_table_node {
    void *key;
    void *value;
    size_t hash;
} h_table_node;


h_table *h_table_new(h_table_cmp cmp);
void h_table_free(h_table *_h_table, h_table_cb cb);
void *h_table_get(h_table *_h_table, void *key);
void h_table_set(h_table *_h_table, void *key, void *value);
void *h_table_remove(h_table *_h_table, void *key, h_table_cb cb);
void h_table_traverse(h_table *_h_table, h_table_cb cb);

// Macro Usage:
// H_TABLE_FOREACH(h_table) {
    // use elem
    // elem is the current h_table_node
// } H_TABLE_FOREACH_END
#define H_TABLE_FOREACH(h_table) \
    if ((h_table)->buckets) { \
        for (unsigned int i = 0; i < (h_table)->buckets->len; i++) { \
            array *bucket = array_get((h_table)->buckets, i); \
            if (bucket) { \
                for (unsigned int j = 0; j < bucket->len; j++) { \
                    h_table_node *elem = array_get(bucket, j); \
                    if (elem)

#define H_TABLE_FOREACH_END } } } }

#endif
