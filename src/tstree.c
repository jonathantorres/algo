#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include "tstree.h"

static inline tstree *tstree_insert_base(tstree *root, tstree *node, const char *key, size_t len, void *value)
{
    if (node == NULL) {
        node = (tstree *)calloc(1, sizeof(tstree));

        if (root == NULL) {
            root = node;
        }

        node->splitchar = *key;
    }

    if (*key < node->splitchar) {
        node->low = tstree_insert_base(root, node->low, key, len, value);
    } else if (*key == node->splitchar) {
        if (len > 1) {
            node->equal = tstree_insert_base(root, node->equal, key + 1, len - 1, value);
        } else {
            assert(node->value == NULL && "Duplicate insert into tst.");
            node->value = value;
        }
    } else {
        node->high = tstree_insert_base(root, node->high, key, len, value);
    }

    return node;
}

tstree *tstree_insert(tstree *node, const char *key, size_t len, void *value)
{
    return tstree_insert_base(node, node, key, len, value);
}

void *tstree_search(tstree *root, const char *key, size_t len)
{
    tstree *node = root;
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

void *tstree_search_prefix(tstree *root, const char *key, size_t len)
{
    if (len == 0) {
        return NULL;
    }

    tstree *node = root;
    tstree *last = NULL;
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

void tstree_traverse(tstree *node, tstree_traverse_cb cb, void *data)
{
    if (!node) {
        return;
    }

    if (node->low) {
        tstree_traverse(node->low, cb, data);
    }

    if (node->equal) {
        tstree_traverse(node->equal, cb, data);
    }

    if (node->high) {
        tstree_traverse(node->high, cb, data);
    }

    if (node->value) {
        cb(node->value, data);
    }
}

void tstree_destroy(tstree *node)
{
    if (node == NULL) {
        return;
    }

    if (node->low) {
        tstree_destroy(node->low);
    }

    if (node->equal) {
        tstree_destroy(node->equal);
    }

    if (node->high) {
        tstree_destroy(node->high);
    }

    free(node);
}
