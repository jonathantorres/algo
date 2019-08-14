#include "bstree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int default_compare(void *a, void *b)
{
    return 0; // FIX!
}

static int bstree_destroy_cb(bstree_node *node)
{
    free(node);
    return 0;
}

static inline bstree_node *bstree_node_create(bstree_node *parent, void *key, void *value)
{
    bstree_node *node = calloc(1, sizeof(bstree_node));

    if (!node) {
        return NULL;
    }

    node->key = key;
    node->value = value;
    node->parent = parent;

    return node;
}

static inline void bstree_set_node(bstree *tree, bstree_node *node, void *key, void *value)
{
    int cmp = tree->compare(node->key, key);

    if (cmp <= 0) {
        if (node->left) {
            bstree_set_node(tree, node->left, key, value);
        } else {
            node->left = bstree_node_create(node, key, value);
        }
    } else {
        if (node->right) {
            bstree_set_node(tree, node->right, key, value);
        } else {
            node->right = bstree_node_create(node, key, value);
        }
    }
}

static inline bstree_node *bstree_get_node(bstree *tree, bstree_node *node, void *key)
{
    int cmp = tree->compare(node->key, key);

    if (cmp == 0) {
        return node;
    } else if (cmp < 0) {
        if (node->left) {
            return bstree_get_node(tree, node->left, key);
        } else {
            return NULL;
        }
    } else {
        if (node->right) {
            return bstree_get_node(tree, node->right, key);
        } else {
            return NULL;
        }
    }
}

static inline int bstree_traverse_nodes(bstree_node *node, bstree_traverse_cb traverse_cb)
{
    int rc = 0;

    if (node->left) {
        rc = bstree_traverse_nodes(node->left, traverse_cb);
        if (rc != 0) {
            return rc;
        }
    }

    if (node->right) {
        rc = bstree_traverse_nodes(node->right, traverse_cb);
        if (rc != 0) {
            return rc;
        }
    }

    return traverse_cb(node);
}

static inline bstree_node *bstree_find_min(bstree_node *node)
{
    while (node->left) {
        node = node->left;
    }

    return node;
}

static inline void bstree_replace_node_in_parent(bstree *tree, bstree_node *node, bstree_node *new_value)
{
    if (node->parent) {
        if (node == node->parent->left) {
            node->parent->left = new_value;
        } else {
            node->parent->right = new_value;
        }
    } else {
        // this is the root, so gotta change it
        tree->root = new_value;
    }

    if (new_value) {
        new_value->parent = node->parent;
    }
}

static inline void bstree_swap(bstree_node *a, bstree_node *b)
{
    void *temp = NULL;
    temp = b->key;
    b->key = a->key;
    a->key = temp;

    temp = b->value;
    b->value = a->value;
    a->value = temp;
}

static inline bstree_node *bstree_node_delete(bstree *tree, bstree_node *node, void *key)
{
    int cmp = tree->compare(node->key, key);

    if (cmp < 0) {
        if (node->left) {
            return bstree_node_delete(tree, node->left, key);
        } else {
            // not found
            return NULL;
        }
    } else if (cmp > 0) {
        if (node->right) {
            return bstree_node_delete(tree, node->right, key);
        } else {
            // not found
            return NULL;
        }
    } else {
        if (node->left && node->right) {
            // swap this node for the smallest node that is bigger than us
            bstree_node *successor = bstree_find_min(node->right);
            bstree_swap(successor, node);

            // this leaves the old successor with possibly a right child
            // so replace it with that right child
            bstree_replace_node_in_parent(tree, successor, successor->right);

            // finally it's swapped, so return successor instead of node
            return  successor;
        } else if (node->left) {
            bstree_replace_node_in_parent(tree, node, node->left);
        } else if (node->right) {
            bstree_replace_node_in_parent(tree, node, node->right);
        } else {
            bstree_replace_node_in_parent(tree, node, NULL);
        }

        return node;
    }
}

bstree *bstree_create(bstree_compare compare)
{
    bstree *tree = calloc(1, sizeof(bstree));

    if (!tree) {
        fputs("[bstree_create] Not enough memory.", stderr);
        return NULL;
    }

    tree->compare = compare == NULL ? default_compare : compare;
    tree->count = 0;
    tree->root = NULL;

    return tree;
}

void bstree_destroy(bstree *tree)
{
    if (tree) {
        bstree_traverse(tree, bstree_destroy_cb);
        free(tree);
    }
}

int bstree_set(bstree *tree, void *key, void *value)
{
    if (tree->root == NULL) {
        // first, so just make it and get out
        tree->root = bstree_node_create(NULL, key, value);

        if (!tree->root) {
            return -1;
        }
    } else {
        bstree_set_node(tree, tree->root, key, value);
    }

    return 0;
}

void *bstree_get(bstree *tree, void *key)
{
    if (tree->root == NULL) {
        return NULL;
    } else {
        bstree_node *node = bstree_get_node(tree, tree->root, key);
        return node == NULL ? NULL : node->value;
    }
}

int bstree_traverse(bstree *tree, bstree_traverse_cb traverse_cb)
{
    if (tree->root) {
        return bstree_traverse_nodes(tree->root, traverse_cb);
    }

    return 0;
}

void *bstree_delete(bstree *tree, void *key)
{
    void *value = NULL;

    if (tree->root) {
        bstree_node *node = bstree_node_delete(tree, tree->root, key);

        if (node) {
            value = node->value;
            free(node);
        }
    }

    return value;
}
