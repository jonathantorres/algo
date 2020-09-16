#include "rb_tree.h"

rb_tree_node *_rb_tree_create_node(void *value)
{
    rb_tree_node *node = malloc(sizeof(rb_tree_node));
    if (!node) {
        return NULL;
    }

    node->value = value;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void _rb_tree_insert_node(rb_tree *tree, rb_tree_node **node, rb_tree_node *parent, void *value, rb_tree_cmp cmp)
{
    if (*node == NULL) {
        rb_tree_node *new_node = _rb_tree_create_node(value);
        new_node->parent = parent;
        *node = new_node;
        tree->len++;
        return;
    }

    if (cmp(value, (*node)->value) < 0) {
        _rb_tree_insert_node(tree, &(*node)->left, *node, value, cmp);
    } else {
        _rb_tree_insert_node(tree, &(*node)->right, *node, value, cmp);
    }
}

void _rb_tree_traverse_node(rb_tree_node *node, rb_tree_cb cb)
{
    if (!node) {
        return;
    }
    _rb_tree_traverse_node(node->left, cb);
    if (cb) {
        cb(node);
    }
    _rb_tree_traverse_node(node->right, cb);
}

void _rb_tree_destroy_node(rb_tree_node *node)
{
    if (!node) {
        return;
    }

    _rb_tree_destroy_node(node->left);
    _rb_tree_destroy_node(node->right);
    free(node);
}

void _rb_tree_destroy_single_node(rb_tree_node *node, rb_tree_cb cb)
{
    if (!node) {
        return;
    }
    if (cb) {
        cb(node);
    }
    free(node);
}

rb_tree_node *_rb_tree_find_node(rb_tree_node *node, void *value, rb_tree_cmp cmp)
{
    if (!node) {
        return NULL;
    }
    int result = cmp(value, node->value);

    if (result == 0) {
        return node;
    } else if (result < 0) {
        return _rb_tree_find_node(node->left, value, cmp);
    } else if (result > 0) {
        return _rb_tree_find_node(node->right, value, cmp);
    }

    return NULL;
}

rb_tree_node *_rb_tree_find_min_node(rb_tree_node *node)
{
    rb_tree_node *min_node = node;

    while (min_node->left != NULL) {
        min_node = min_node->left;
    }
    return min_node;
}

rb_tree_node *_rb_tree_find_max_node(rb_tree_node *node)
{
    rb_tree_node *max_node = node;

    while (max_node->right != NULL) {
        max_node = max_node->right;
    }
    return max_node;
}

rb_tree_node *_rb_tree_update_parent_node(rb_tree_node *node_to_delete, rb_tree_node *node_to_move)
{
    if (node_to_move) {
        node_to_move->parent = node_to_delete->parent;
    }
    if (node_to_delete->parent) {
        if (node_to_delete == node_to_delete->parent->left) {
            if (node_to_move) {
                node_to_move->parent->left = node_to_move;
            } else {
                node_to_delete->parent->left = node_to_move;
            }
        } else if (node_to_delete == node_to_delete->parent->right) {
            if (node_to_move) {
                node_to_move->parent->right = node_to_move;
            } else {
                node_to_delete->parent->right = node_to_move;
            }
        }
    }

    return node_to_move;
}

rb_tree *rb_tree_new(rb_tree_cmp cmp)
{
    rb_tree *tree = malloc(sizeof(rb_tree));

    if (!tree) {
        return NULL;
    }
    tree->len = 0;
    tree->root = NULL;
    tree->cmp = cmp;

    return tree;
}

void rb_tree_insert(rb_tree *tree, void *value)
{
    if (!tree) {
        return;
    }
    if (tree->root == NULL) {
        rb_tree_node *node = _rb_tree_create_node(value);
        if (!node) {
            return;
        }

        tree->root = node;
        tree->len++;
        return;
    }

    _rb_tree_insert_node(tree, &tree->root, tree->root, value, tree->cmp);
    return;
}

// TODO: most likely refactor this thing
void rb_tree_delete(rb_tree *tree, void *value, rb_tree_cb cb)
{
    if (!tree) {
        return;
    }
    if (tree->root == NULL) {
        return;
    }

    bool deleted_root = false;
    rb_tree_node *node_to_delete = _rb_tree_find_node(tree->root, value, tree->cmp);
    if (node_to_delete == NULL) {
        return;
    }
    if (node_to_delete == tree->root) {
        deleted_root = true;
    }

    // let's delete the node
    if (node_to_delete->left == NULL && node_to_delete->right == NULL) {
        // node with no children
        rb_tree_node *new_root = _rb_tree_update_parent_node(node_to_delete, NULL);
        if (deleted_root) {
            tree->root = new_root;
        }
        _rb_tree_destroy_single_node(node_to_delete, cb);
    } else if (node_to_delete->left == NULL && node_to_delete->right != NULL) {
        // node with a right child
        rb_tree_node *new_root = _rb_tree_update_parent_node(node_to_delete, node_to_delete->right);
        if (deleted_root) {
            tree->root = new_root;
        }
        _rb_tree_destroy_single_node(node_to_delete, cb);
    } else if (node_to_delete->left != NULL && node_to_delete->right == NULL) {
        // node with a left child
        rb_tree_node *new_root = _rb_tree_update_parent_node(node_to_delete, node_to_delete->left);
        if (deleted_root) {
            tree->root = new_root;
        }
        _rb_tree_destroy_single_node(node_to_delete, cb);
    } else if (node_to_delete->left != NULL && node_to_delete->right != NULL) {
        // node with left and right children
        rb_tree_node *replacement = _rb_tree_find_min_node(node_to_delete->right);
        if (replacement->parent) {
            if (replacement->parent->left == replacement) {
                replacement->parent->left = NULL;
            }
        }
        replacement->parent = node_to_delete->parent;

        if (node_to_delete->parent != NULL) {
            if (node_to_delete->parent->right == node_to_delete) {
                node_to_delete->parent->right = replacement;
            } else if (node_to_delete->parent->left == node_to_delete) {
                node_to_delete->parent->left = replacement;
            }
        }

        // using just the right node as the replacement
        if (node_to_delete->right == replacement) {
            replacement->right = NULL;
            replacement->left = node_to_delete->left;
            node_to_delete->left->parent = replacement;
        } else {
            replacement->right = node_to_delete->right;
            replacement->left = node_to_delete->left;
            node_to_delete->left->parent = replacement;
            node_to_delete->right->parent = replacement;
        }
        if (deleted_root) {
            tree->root = replacement;
        }
        _rb_tree_destroy_single_node(node_to_delete, cb);
    }
    tree->len--;
}

void *rb_tree_search(rb_tree *tree, void *value)
{
    if (!tree) {
        return NULL;
    }
    if (tree->root == NULL) {
        return NULL;
    }

    rb_tree_node *node_found = _rb_tree_find_node(tree->root, value, tree->cmp);
    if (!node_found) {
        return NULL;
    }

    return node_found->value;
}

void *rb_tree_find_max(rb_tree *tree)
{
    if (!tree) {
        return NULL;
    }
    if (tree->root == NULL) {
        return NULL;
    }

    rb_tree_node *max_node = _rb_tree_find_max_node(tree->root);
    if (max_node == NULL) {
        return NULL;
    }

    return max_node->value;
}

void *rb_tree_find_min(rb_tree *tree)
{
    if (!tree) {
        return NULL;
    }
    if (tree->root == NULL) {
        return NULL;
    }

    rb_tree_node *min_node = _rb_tree_find_min_node(tree->root);
    if (min_node == NULL) {
        return NULL;
    }

    return min_node->value;
}

void rb_tree_traverse(rb_tree *tree, rb_tree_cb cb)
{
    if (!tree) {
        return;
    }
    if (tree->root == NULL) {
        return;
    }

    _rb_tree_traverse_node(tree->root, cb);
}

void rb_tree_free(rb_tree *tree, rb_tree_cb cb)
{
    if (!tree) {
        return;
    }
    if (tree->root == NULL) {
        return;
    }

    rb_tree_traverse(tree, cb);
    _rb_tree_destroy_node(tree->root);

    if (tree) {
        free(tree);
    }
}
