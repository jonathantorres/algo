#include "bs_tree.h"

bs_tree_node *_bs_tree_find_node(bs_tree_node *node, void *value, bs_tree_cmp cmp)
{
    if (!node) {
        return NULL;
    }
    int result = cmp(value, node->value);

    if (result == 0) {
        return node;
    } else if (result < 0) {
        return _bs_tree_find_node(node->left, value, cmp);
    } else if (result > 0) {
        return _bs_tree_find_node(node->right, value, cmp);
    }

    return NULL;
}

bs_tree_node *_bs_tree_find_min_node(bs_tree_node *node)
{
    bs_tree_node *min_node = node;

    while (min_node->left != NULL) {
        min_node = min_node->left;
    }
    return min_node;
}

bs_tree_node *_bs_tree_find_max_node(bs_tree_node *node)
{
    bs_tree_node *max_node = node;

    while (max_node->right != NULL) {
        max_node = max_node->right;
    }
    return max_node;
}

bs_tree_node *_bs_tree_create_node(void *value)
{
    bs_tree_node *node = malloc(sizeof(bs_tree_node));
    if (!node) {
        return NULL;
    }

    node->value = value;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void _bs_tree_insert_node(bs_tree *tree, bs_tree_node **node, bs_tree_node *parent, void *value, bs_tree_cmp cmp)
{
    if (*node == NULL) {
        bs_tree_node *new_node = _bs_tree_create_node(value);
        new_node->parent = parent;
        *node = new_node;
        tree->len++;
        return;
    }

    if (cmp(value, (*node)->value) < 0) {
        _bs_tree_insert_node(tree, &(*node)->left, *node, value, cmp);
    } else {
        _bs_tree_insert_node(tree, &(*node)->right, *node, value, cmp);
    }
}

void _bs_tree_traverse_node(bs_tree_node *node, bs_tree_cb cb)
{
    if (!node) {
        return;
    }
    _bs_tree_traverse_node(node->left, cb);
    cb(node);
    _bs_tree_traverse_node(node->right, cb);
}

void _bs_tree_destroy_node(bs_tree_node *node)
{
    if (!node) {
        return;
    }

    _bs_tree_destroy_node(node->left);
    _bs_tree_destroy_node(node->right);
    free(node);
}

void _bs_tree_destroy_single_node(bs_tree_node *node, bs_tree_cb cb)
{
    if (!node) {
        return;
    }
    cb(node);
    free(node);
}

bs_tree *bs_tree_new(bs_tree_cmp cmp)
{
    bs_tree *tree = malloc(sizeof(bs_tree));

    if (!tree) {
        return NULL;
    }
    tree->len = 0;
    tree->root = NULL;
    tree->cmp = cmp;

    return tree;
}

void bs_tree_insert(bs_tree *tree, void *value)
{
    if (!tree) {
        return;
    }
    if (tree->root == NULL) {
        bs_tree_node *node = _bs_tree_create_node(value);
        if (!node) {
            return;
        }

        tree->root = node;
        tree->len++;
        return;
    }

    _bs_tree_insert_node(tree, &tree->root, tree->root, value, tree->cmp);
    return;
}

void bs_tree_delete(bs_tree *tree, void *value, bs_tree_cb cb)
{
    if (!tree) {
        return;
    }
    if (tree->root == NULL) {
        return;
    }

    bool deleted_root = false;
    bs_tree_node *node_to_delete = _bs_tree_find_node(tree->root, value, tree->cmp);
    if (node_to_delete == NULL) {
        return;
    }

    if (node_to_delete == tree->root) {
        deleted_root = true;
    }

    // let's delete the node
    if (node_to_delete->left == NULL && node_to_delete->right == NULL) {
        // node with no children
        if (node_to_delete == node_to_delete->parent->left) {
            node_to_delete->parent->left = NULL;
        } else if (node_to_delete == node_to_delete->parent->right) {
            node_to_delete->parent->right = NULL;
        }
        if (deleted_root) {
            tree->root = NULL;
        }
        _bs_tree_destroy_single_node(node_to_delete, cb);
    } else if (node_to_delete->left == NULL && node_to_delete->right != NULL) {
        // node with a right child
        bs_tree_node *node_to_move = node_to_delete->right;
        node_to_move->parent = node_to_delete->parent;
        if (node_to_delete->parent->right == node_to_delete) {
            node_to_move->parent->right = node_to_move;
        } else if (node_to_delete->parent->left == node_to_delete) {
            node_to_move->parent->left = node_to_move;
        }
        if (deleted_root) {
            tree->root = node_to_move;
        }
        _bs_tree_destroy_single_node(node_to_delete, cb);
    } else if (node_to_delete->left != NULL && node_to_delete->right == NULL) {
        // node with a left child
        bs_tree_node *node_to_move = node_to_delete->left;
        node_to_move->parent = node_to_delete->parent;
        if (node_to_delete->parent->right == node_to_delete) {
            node_to_move->parent->right = node_to_move;
        } else if (node_to_delete->parent->left == node_to_delete) {
            node_to_move->parent->left = node_to_move;
        }
        if (deleted_root) {
            tree->root = node_to_move;
        }
        _bs_tree_destroy_single_node(node_to_delete, cb);
    } else if (node_to_delete->left != NULL && node_to_delete->right != NULL) {
        // node with left and right children
        bs_tree_node *replacement = _bs_tree_find_min_node(node_to_delete->right);
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
        _bs_tree_destroy_single_node(node_to_delete, cb);
    }
    tree->len--;
}

void *bs_tree_search(bs_tree *tree, void *value)
{
    if (!tree) {
        return NULL;
    }
    if (tree->root == NULL) {
        return NULL;
    }

    bs_tree_node *node_found = _bs_tree_find_node(tree->root, value, tree->cmp);
    if (!node_found) {
        return NULL;
    }

    return node_found->value;
}

void *bs_tree_find_max(bs_tree *tree)
{
    if (!tree) {
        return NULL;
    }
    if (tree->root == NULL) {
        return NULL;
    }

    bs_tree_node *max_node = _bs_tree_find_max_node(tree->root);
    if (max_node == NULL) {
        return NULL;
    }

    return max_node->value;
}

void *bs_tree_find_min(bs_tree *tree)
{
    if (!tree) {
        return NULL;
    }
    if (tree->root == NULL) {
        return NULL;
    }

    bs_tree_node *min_node = _bs_tree_find_min_node(tree->root);
    if (min_node == NULL) {
        return NULL;
    }

    return min_node->value;
}

void bs_tree_traverse(bs_tree *tree, bs_tree_cb cb)
{
    if (!tree) {
        return;
    }
    if (tree->root == NULL) {
        return;
    }

    _bs_tree_traverse_node(tree->root, cb);
}

void bs_tree_free(bs_tree *tree, bs_tree_cb cb)
{
    if (!tree) {
        return;
    }
    if (tree->root == NULL) {
        return;
    }

    bs_tree_traverse(tree, cb);
    _bs_tree_destroy_node(tree->root);

    if (tree) {
        free(tree);
    }
}
