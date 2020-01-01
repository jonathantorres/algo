#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include "ts_tree.h"

static inline ts_tree *_ts_tree_insert_base(ts_tree *root, ts_tree *node, const char *key, size_t len, void *value)
{
    if (node == NULL) {
        node = (ts_tree *)calloc(1, sizeof(ts_tree));

        if (root == NULL) {
            root = node;
        }

        node->splitchar = *key;
    }

    if (*key < node->splitchar) {
        node->low = _ts_tree_insert_base(root, node->low, key, len, value);
    } else if (*key == node->splitchar) {
        if (len > 1) {
            node->equal = _ts_tree_insert_base(root, node->equal, key + 1, len - 1, value);
        } else {
            assert(node->value == NULL && "Duplicate insert into tst.");
            node->value = value;
        }
    } else {
        node->high = _ts_tree_insert_base(root, node->high, key, len, value);
    }

    return node;
}

ts_tree *ts_tree_insert(ts_tree *node, const char *key, size_t len, void *value)
{
    return _ts_tree_insert_base(node, node, key, len, value);
}

void *ts_tree_search(ts_tree *root, const char *key, size_t len)
{
    ts_tree *node = root;
    size_t i = 0;

    while (i < len && node) {
        if (key[i] < node->splitchar) {
            node = node->low;
        } else if (key[i] == node->splitchar) {
            i++;
            if (i < len) {
                node = node->equal;
            }
        } else {
            node = node->high;
        }
    }

    if (node) {
        return node->value;
    } else {
        return NULL;
    }
}

void *ts_tree_search_prefix(ts_tree *root, const char *key, size_t len)
{
    if (len == 0) {
        return NULL;
    }

    ts_tree *node = root;
    ts_tree *last = NULL;
    size_t i = 0;

    while (i < len && node) {
        if (key[i] < node->splitchar) {
            node = node->low;
        } else if (key[i] == node->splitchar) {
            i++;
            if (i < len) {
                if (node->value) {
                    last = node;
                }
                node = node->equal;
            }
        } else {
            node = node->high;
        }
    }

    node = node ? node : last;

    // traverse until we find the first value in the equal chain
    // this is then the first node with this prefix
    while (node && !node->value) {
        node = node->equal;
    }

    return node ? node->value : NULL;
}

void ts_tree_traverse(ts_tree *node, ts_tree_traverse_cb cb, void *data)
{
    if (!node) {
        return;
    }

    if (node->low) {
        ts_tree_traverse(node->low, cb, data);
    }

    if (node->equal) {
        ts_tree_traverse(node->equal, cb, data);
    }

    if (node->high) {
        ts_tree_traverse(node->high, cb, data);
    }

    if (node->value) {
        cb(node->value, data);
    }
}

void ts_tree_destroy(ts_tree *node)
{
    if (node == NULL) {
        return;
    }

    if (node->low) {
        ts_tree_destroy(node->low);
    }

    if (node->equal) {
        ts_tree_destroy(node->equal);
    }

    if (node->high) {
        ts_tree_destroy(node->high);
    }

    free(node);
}
