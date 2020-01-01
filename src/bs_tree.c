#include "bs_tree.h"

static int _bs_tree_default_compare(void *a, void *b)
{
    return strcmp((char*)a, (char*)b);
}

static int _bs_tree_destroy_cb(bs_tree_node *node)
{
    free(node);
    return 0;
}

static inline bs_tree_node *_bs_tree_node_create(bs_tree_node *parent, void *key, void *value)
{
    bs_tree_node *node = calloc(1, sizeof(bs_tree_node));

    if (!node) {
        return NULL;
    }

    node->key = key;
    node->value = value;
    node->parent = parent;

    return node;
}

static inline void _bs_tree_set_node(bs_tree *tree, bs_tree_node *node, void *key, void *value)
{
    int cmp = tree->compare(node->key, key);

    if (cmp <= 0) {
        if (node->left) {
            _bs_tree_set_node(tree, node->left, key, value);
        } else {
            node->left = _bs_tree_node_create(node, key, value);
        }
    } else {
        if (node->right) {
            _bs_tree_set_node(tree, node->right, key, value);
        } else {
            node->right = _bs_tree_node_create(node, key, value);
        }
    }
}

static inline bs_tree_node *_bs_tree_get_node(bs_tree *tree, bs_tree_node *node, void *key)
{
    int cmp = tree->compare(node->key, key);

    if (cmp == 0) {
        return node;
    } else if (cmp < 0) {
        if (node->left) {
            return _bs_tree_get_node(tree, node->left, key);
        } else {
            return NULL;
        }
    } else {
        if (node->right) {
            return _bs_tree_get_node(tree, node->right, key);
        } else {
            return NULL;
        }
    }
}

static inline int _bs_tree_traverse_nodes(bs_tree_node *node, bs_tree_traverse_cb traverse_cb)
{
    int rc = 0;

    if (node->left) {
        rc = _bs_tree_traverse_nodes(node->left, traverse_cb);
        if (rc != 0) {
            return rc;
        }
    }

    if (node->right) {
        rc = _bs_tree_traverse_nodes(node->right, traverse_cb);
        if (rc != 0) {
            return rc;
        }
    }

    return traverse_cb(node);
}

static inline bs_tree_node *_bs_tree_find_min(bs_tree_node *node)
{
    while (node->left) {
        node = node->left;
    }

    return node;
}

static inline void _bs_tree_replace_node_in_parent(bs_tree *tree, bs_tree_node *node, bs_tree_node *new_value)
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

static inline void _bs_tree_swap(bs_tree_node *a, bs_tree_node *b)
{
    void *temp = NULL;
    temp = b->key;
    b->key = a->key;
    a->key = temp;

    temp = b->value;
    b->value = a->value;
    a->value = temp;
}

static inline bs_tree_node *_bs_tree_node_delete(bs_tree *tree, bs_tree_node *node, void *key)
{
    int cmp = tree->compare(node->key, key);

    if (cmp < 0) {
        if (node->left) {
            return _bs_tree_node_delete(tree, node->left, key);
        } else {
            // not found
            return NULL;
        }
    } else if (cmp > 0) {
        if (node->right) {
            return _bs_tree_node_delete(tree, node->right, key);
        } else {
            // not found
            return NULL;
        }
    } else {
        if (node->left && node->right) {
            // swap this node for the smallest node that is bigger than us
            bs_tree_node *successor = _bs_tree_find_min(node->right);
            _bs_tree_swap(successor, node);

            // this leaves the old successor with possibly a right child
            // so replace it with that right child
            _bs_tree_replace_node_in_parent(tree, successor, successor->right);

            // finally it's swapped, so return successor instead of node
            return  successor;
        } else if (node->left) {
            _bs_tree_replace_node_in_parent(tree, node, node->left);
        } else if (node->right) {
            _bs_tree_replace_node_in_parent(tree, node, node->right);
        } else {
            _bs_tree_replace_node_in_parent(tree, node, NULL);
        }

        return node;
    }
}

bs_tree *bs_tree_create(bs_tree_compare compare)
{
    bs_tree *tree = calloc(1, sizeof(bs_tree));

    if (!tree) {
        fputs("[bs_tree_create] Not enough memory.", stderr);
        return NULL;
    }

    tree->compare = compare == NULL ? _bs_tree_default_compare : compare;
    tree->count = 0;
    tree->root = NULL;

    return tree;
}

void bs_tree_destroy(bs_tree *tree)
{
    if (tree) {
        bs_tree_traverse(tree, _bs_tree_destroy_cb);
        free(tree);
    }
}

int bs_tree_set(bs_tree *tree, void *key, void *value)
{
    if (tree->root == NULL) {
        // first, so just make it and get out
        tree->root = _bs_tree_node_create(NULL, key, value);

        if (!tree->root) {
            return -1;
        }
    } else {
        _bs_tree_set_node(tree, tree->root, key, value);
    }

    return 0;
}

void *bs_tree_get(bs_tree *tree, void *key)
{
    if (tree->root == NULL) {
        return NULL;
    } else {
        bs_tree_node *node = _bs_tree_get_node(tree, tree->root, key);
        return node == NULL ? NULL : node->value;
    }
}

int bs_tree_traverse(bs_tree *tree, bs_tree_traverse_cb traverse_cb)
{
    if (tree->root) {
        return _bs_tree_traverse_nodes(tree->root, traverse_cb);
    }

    return 0;
}

void *bs_tree_delete(bs_tree *tree, void *key)
{
    void *value = NULL;

    if (tree->root) {
        bs_tree_node *node = _bs_tree_node_delete(tree, tree->root, key);

        if (node) {
            value = node->value;
            free(node);
        }
    }

    return value;
}
