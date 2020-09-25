#include "rb_tree.h"

rb_tree_node *_rb_tree_create_sentinel()
{
    rb_tree_node *node = malloc(sizeof(rb_tree_node));
    if (!node) {
        return NULL;
    }

    node->value = NULL;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    rb_tree_black(node);

    return node;
}

rb_tree_node *_rb_tree_create_node(void *value, rb_tree_node *sentinel)
{
    rb_tree_node *node = malloc(sizeof(rb_tree_node));
    if (!node) {
        return NULL;
    }

    node->value = value;
    node->parent = NULL;
    node->left = sentinel;
    node->right = sentinel;
    rb_tree_red(node);

    return node;
}

rb_tree_node *_rb_tree_insert_node(rb_tree *tree, rb_tree_node **node, rb_tree_node *parent, void *value, rb_tree_cmp cmp)
{
    rb_tree_node *new_node = NULL;
    if (*node == tree->sentinel) {
        new_node = _rb_tree_create_node(value, tree->sentinel);
        new_node->parent = parent;
        *node = new_node;
        tree->len++;
        return new_node;
    }

    if (cmp(value, (*node)->value) < 0) {
        return _rb_tree_insert_node(tree, &(*node)->left, *node, value, cmp);
    }
    return _rb_tree_insert_node(tree, &(*node)->right, *node, value, cmp);
}

void _rb_tree_traverse_node(rb_tree_node *node, rb_tree_node *sentinel, rb_tree_cb cb)
{
    if (node == sentinel) {
        return;
    }
    _rb_tree_traverse_node(node->left, sentinel, cb);
    if (cb) {
        cb(node->value);
    }
    _rb_tree_traverse_node(node->right, sentinel, cb);
}

void _rb_tree_destroy_node(rb_tree_node *node, rb_tree_node *sentinel)
{
    if (node == sentinel) {
        return;
    }

    _rb_tree_destroy_node(node->left, sentinel);
    _rb_tree_destroy_node(node->right, sentinel);
    free(node);
}

void _rb_tree_destroy_single_node(rb_tree_node *node, rb_tree_cb cb)
{
    if (!node) {
        return;
    }
    if (cb) {
        cb(node->value);
    }
    free(node);
}

rb_tree_node *_rb_tree_find_node(rb_tree_node *node, rb_tree_node *sentinel, void *value, rb_tree_cmp cmp)
{
    if (node == sentinel) {
        return NULL;
    }
    int result = cmp(value, node->value);

    if (result == 0) {
        return node;
    } else if (result < 0) {
        return _rb_tree_find_node(node->left, sentinel, value, cmp);
    } else if (result > 0) {
        return _rb_tree_find_node(node->right, sentinel, value, cmp);
    }

    return NULL;
}

rb_tree_node *_rb_tree_find_min_node(rb_tree_node *node, rb_tree_node *sentinel)
{
    rb_tree_node *min_node = node;

    while (min_node->left != sentinel) {
        min_node = min_node->left;
    }
    return min_node;
}

rb_tree_node *_rb_tree_find_max_node(rb_tree_node *node, rb_tree_node *sentinel)
{
    rb_tree_node *max_node = node;

    while (max_node->right != sentinel) {
        max_node = max_node->right;
    }
    return max_node;
}

void _rb_tree_left_rotate(rb_tree *tree, rb_tree_node *node)
{
    rb_tree_node *tmp = node->right;
    node->right = tmp->left;
    if (tmp->left != tree->sentinel) {
        tmp->left->parent = node;
    }
    tmp->parent = node->parent;
    if (node->parent == tree->sentinel) {
        tree->root = tmp;
    } else if (node == node->parent->left) {
        node->parent->left = tmp;
    } else {
        node->parent->right = tmp;
    }
    tmp->left = node;
    node->parent = tmp;
}

void _rb_tree_right_rotate(rb_tree *tree, rb_tree_node *node)
{
    rb_tree_node *tmp = node->left;
    node->left = tmp->right;
    if (tmp->right != tree->sentinel) {
        tmp->right->parent = node;
    }
    tmp->parent = node->parent;
    if (node->parent == tree->sentinel) {
        tree->root = tmp;
    } else if (node == node->parent->left) {
        node->parent->left = tmp;
    } else {
        node->parent->right = tmp;
    }
    tmp->right = node;
    node->parent = tmp;
}

rb_tree_node *_rb_tree_update_parent_node(rb_tree_node *node_to_delete, rb_tree_node *node_to_move, rb_tree_node *sentinel)
{
    if (node_to_move != sentinel) {
        node_to_move->parent = node_to_delete->parent;
    }
    if (node_to_delete->parent != sentinel) {
        if (node_to_delete == node_to_delete->parent->left) {
            if (node_to_move != sentinel) {
                node_to_move->parent->left = node_to_move;
            } else {
                node_to_delete->parent->left = node_to_move;
            }
        } else if (node_to_delete == node_to_delete->parent->right) {
            if (node_to_move != sentinel) {
                node_to_move->parent->right = node_to_move;
            } else {
                node_to_delete->parent->right = node_to_move;
            }
        }
    }

    return node_to_move;
}

void _rb_tree_insert_fixup(rb_tree *tree, rb_tree_node *node)
{
    while (node != tree->root && rb_tree_is_red(node->parent)) {
        if (node->parent == node->parent->parent->left) {
            rb_tree_node *right_node = node->parent->parent->right;
            if (rb_tree_is_red(right_node)) {
                rb_tree_black(node->parent);
                rb_tree_black(right_node);
                rb_tree_red(node->parent->parent);
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    _rb_tree_left_rotate(tree, node);
                }
                rb_tree_black(node->parent);
                rb_tree_red(node->parent->parent);
                _rb_tree_right_rotate(tree, node->parent->parent);
            }
        } else {
            rb_tree_node *left_node = node->parent->parent->left;
            if (rb_tree_is_red(left_node)) {
                rb_tree_black(node->parent);
                rb_tree_black(left_node);
                rb_tree_red(node->parent->parent);
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    _rb_tree_right_rotate(tree, node);
                }
                rb_tree_black(node->parent);
                rb_tree_red(node->parent->parent);
                _rb_tree_left_rotate(tree, node->parent->parent);
            }
        }
    }
    rb_tree_black(tree->root);
}

rb_tree *rb_tree_new(rb_tree_cmp cmp)
{
    rb_tree *tree = malloc(sizeof(rb_tree));

    if (!tree) {
        return NULL;
    }

    rb_tree_node *s = _rb_tree_create_sentinel();
    if (!s) {
        free(tree);
        return NULL;
    }

    tree->len = 0;
    tree->root = s;
    tree->sentinel = s;
    tree->cmp = cmp;

    return tree;
}

void rb_tree_insert(rb_tree *tree, void *value)
{
    if (!tree) {
        return;
    }
    if (tree->root == tree->sentinel) {
        rb_tree_node *node = _rb_tree_create_node(value, tree->sentinel);
        if (!node) {
            return;
        }
        node->parent = tree->sentinel;
        rb_tree_black(node);
        tree->root = node;
        tree->len++;
        return;
    }

    rb_tree_node *new_node = _rb_tree_insert_node(tree, &tree->root, tree->root, value, tree->cmp);
    _rb_tree_insert_fixup(tree, new_node);
}

void rb_tree_delete(rb_tree *tree, void *value, rb_tree_cb cb)
{
    if (!tree) {
        return;
    }
    if (tree->root == tree->sentinel) {
        return;
    }

    bool deleted_root = false;
    rb_tree_node *node_to_delete = _rb_tree_find_node(tree->root, tree->sentinel, value, tree->cmp);
    if (node_to_delete == NULL) {
        return;
    }
    if (node_to_delete == tree->root) {
        deleted_root = true;
    }

    // let's delete the node
    if (node_to_delete->left == tree->sentinel && node_to_delete->right == tree->sentinel) {
        // node with no children
        rb_tree_node *new_root = _rb_tree_update_parent_node(node_to_delete, tree->sentinel, tree->sentinel);
        if (deleted_root) {
            tree->root = new_root;
        }
        _rb_tree_destroy_single_node(node_to_delete, cb);
    } else if (node_to_delete->left == tree->sentinel && node_to_delete->right != tree->sentinel) {
        // node with a right child
        rb_tree_node *new_root = _rb_tree_update_parent_node(node_to_delete, node_to_delete->right, tree->sentinel);
        if (deleted_root) {
            tree->root = new_root;
        }
        _rb_tree_destroy_single_node(node_to_delete, cb);
    } else if (node_to_delete->left != tree->sentinel && node_to_delete->right == tree->sentinel) {
        // node with a left child
        rb_tree_node *new_root = _rb_tree_update_parent_node(node_to_delete, node_to_delete->left, tree->sentinel);
        if (deleted_root) {
            tree->root = new_root;
        }
        _rb_tree_destroy_single_node(node_to_delete, cb);
    } else if (node_to_delete->left != tree->sentinel && node_to_delete->right != tree->sentinel) {
        // node with left and right children
        rb_tree_node *replacement = _rb_tree_find_min_node(node_to_delete->right, tree->sentinel);
        if (replacement->parent != tree->sentinel) {
            if (replacement->parent->left == replacement) {
                replacement->parent->left = tree->sentinel;
            }
        }
        replacement->parent = node_to_delete->parent;

        if (node_to_delete->parent != tree->sentinel) {
            if (node_to_delete->parent->right == node_to_delete) {
                node_to_delete->parent->right = replacement;
            } else if (node_to_delete->parent->left == node_to_delete) {
                node_to_delete->parent->left = replacement;
            }
        }

        // using just the right node as the replacement
        if (node_to_delete->right == replacement) {
            replacement->right = tree->sentinel;
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

    // TODO: Do rotation stuff
}

void *rb_tree_search(rb_tree *tree, void *value)
{
    if (!tree) {
        return NULL;
    }
    if (tree->root == tree->sentinel) {
        return NULL;
    }

    rb_tree_node *node_found = _rb_tree_find_node(tree->root, tree->sentinel, value, tree->cmp);
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
    if (tree->root == tree->sentinel) {
        return NULL;
    }

    rb_tree_node *max_node = _rb_tree_find_max_node(tree->root, tree->sentinel);
    if (max_node == tree->sentinel) {
        return NULL;
    }

    return max_node->value;
}

void *rb_tree_find_min(rb_tree *tree)
{
    if (!tree) {
        return NULL;
    }
    if (tree->root == tree->sentinel) {
        return NULL;
    }

    rb_tree_node *min_node = _rb_tree_find_min_node(tree->root, tree->sentinel);
    if (min_node == tree->sentinel) {
        return NULL;
    }

    return min_node->value;
}

void rb_tree_traverse(rb_tree *tree, rb_tree_cb cb)
{
    if (!tree) {
        return;
    }
    if (tree->root == tree->sentinel) {
        return;
    }

    _rb_tree_traverse_node(tree->root, tree->sentinel, cb);
}

void rb_tree_free(rb_tree *tree, rb_tree_cb cb)
{
    if (!tree) {
        return;
    }
    if (tree->root == tree->sentinel) {
        free(tree->sentinel);
        free(tree);
        return;
    }

    rb_tree_traverse(tree, cb);
    _rb_tree_destroy_node(tree->root, tree->sentinel);

    if (tree) {
        free(tree->sentinel);
        free(tree);
    }
}
