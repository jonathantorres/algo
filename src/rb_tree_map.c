#include "rb_tree_map.h"

rb_tree_map_node *_rb_tree_map_create_sentinel()
{
    rb_tree_map_node *node = malloc(sizeof(rb_tree_map_node));
    if (!node) {
        return NULL;
    }

    node->key = NULL;
    node->value = NULL;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    rb_tree_map_black(node);

    return node;
}

rb_tree_map_node *_rb_tree_map_create_node(void *key, void *value, rb_tree_map_node *sentinel)
{
    rb_tree_map_node *node = malloc(sizeof(rb_tree_map_node));
    if (!node) {
        return NULL;
    }

    node->key = key;
    node->value = value;
    node->parent = NULL;
    node->left = sentinel;
    node->right = sentinel;
    rb_tree_map_red(node);

    return node;
}

rb_tree_map_node *_rb_tree_map_insert_node(rb_tree_map *tree, rb_tree_map_node **node, rb_tree_map_node *parent, void *key, void *value, rb_tree_map_cmp cmp)
{
    rb_tree_map_node *new_node = NULL;
    if (*node == tree->sentinel) {
        new_node = _rb_tree_map_create_node(key, value, tree->sentinel);
        new_node->parent = parent;
        *node = new_node;
        tree->len++;
        return new_node;
    }

    if (cmp(key, (*node)->key) < 0) {
        return _rb_tree_map_insert_node(tree, &(*node)->left, *node, key, value, cmp);
    }
    return _rb_tree_map_insert_node(tree, &(*node)->right, *node, key, value, cmp);
}

void _rb_tree_map_traverse_node(rb_tree_map_node *node, rb_tree_map_node *sentinel, rb_tree_map_cb cb)
{
    if (node == sentinel) {
        return;
    }
    _rb_tree_map_traverse_node(node->left, sentinel, cb);
    if (cb) {
        cb(node->key, node->value);
    }
    _rb_tree_map_traverse_node(node->right, sentinel, cb);
}

void _rb_tree_map_free_node(rb_tree_map_node *node, rb_tree_map_node *sentinel)
{
    if (node == sentinel) {
        return;
    }

    _rb_tree_map_free_node(node->left, sentinel);
    _rb_tree_map_free_node(node->right, sentinel);
    free(node);
}

void _rb_tree_map_free_single_node(rb_tree_map_node *node, rb_tree_map_node *sentinel, rb_tree_map_cb cb)
{
    if (node == sentinel) {
        return;
    }
    if (cb) {
        cb(node->key, node->value);
    }
    free(node);
}

rb_tree_map_node *_rb_tree_map_find_node(rb_tree_map_node *node, rb_tree_map_node *sentinel, void *key, rb_tree_map_cmp cmp)
{
    if (node == sentinel) {
        return NULL;
    }
    int result = cmp(key, node->key);

    if (result == 0) {
        return node;
    } else if (result < 0) {
        return _rb_tree_map_find_node(node->left, sentinel, key, cmp);
    } else if (result > 0) {
        return _rb_tree_map_find_node(node->right, sentinel, key, cmp);
    }

    return NULL;
}

rb_tree_map_node *_rb_tree_map_find_min_node(rb_tree_map_node *node, rb_tree_map_node *sentinel)
{
    rb_tree_map_node *min_node = node;

    while (min_node->left != sentinel) {
        min_node = min_node->left;
    }
    return min_node;
}

rb_tree_map_node *_rb_tree_map_find_max_node(rb_tree_map_node *node, rb_tree_map_node *sentinel)
{
    rb_tree_map_node *max_node = node;

    while (max_node->right != sentinel) {
        max_node = max_node->right;
    }
    return max_node;
}

void _rb_tree_map_left_rotate(rb_tree_map *tree, rb_tree_map_node *node)
{
    rb_tree_map_node *tmp = node->right;
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

void _rb_tree_map_right_rotate(rb_tree_map *tree, rb_tree_map_node *node)
{
    rb_tree_map_node *tmp = node->left;
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

void _rb_tree_map_insert_fixup(rb_tree_map *tree, rb_tree_map_node *node)
{
    if (!tree) {
        return;
    }
    if (tree->root == tree->sentinel) {
        return;
    }

    while (node != tree->root && rb_tree_map_is_red(node->parent)) {
        if (node->parent == node->parent->parent->left) {
            rb_tree_map_node *right_node = node->parent->parent->right;
            if (rb_tree_map_is_red(right_node)) {
                rb_tree_map_black(node->parent);
                rb_tree_map_black(right_node);
                rb_tree_map_red(node->parent->parent);
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    _rb_tree_map_left_rotate(tree, node);
                }
                rb_tree_map_black(node->parent);
                rb_tree_map_red(node->parent->parent);
                _rb_tree_map_right_rotate(tree, node->parent->parent);
            }
        } else {
            rb_tree_map_node *left_node = node->parent->parent->left;
            if (rb_tree_map_is_red(left_node)) {
                rb_tree_map_black(node->parent);
                rb_tree_map_black(left_node);
                rb_tree_map_red(node->parent->parent);
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    _rb_tree_map_right_rotate(tree, node);
                }
                rb_tree_map_black(node->parent);
                rb_tree_map_red(node->parent->parent);
                _rb_tree_map_left_rotate(tree, node->parent->parent);
            }
        }
    }
    rb_tree_map_black(tree->root);
}

void _rb_tree_map_delete_fixup(rb_tree_map *tree, rb_tree_map_node *node)
{
    if (!tree) {
        return;
    }
    if (tree->root == tree->sentinel) {
        return;
    }

    rb_tree_map_node *tmp = NULL;
    while (node != tree->root && rb_tree_map_is_black(node)) {
        if (node == node->parent->left) {
            tmp = node->parent->right;
            if (rb_tree_map_is_red(tmp)) {
                rb_tree_map_black(tmp);
                rb_tree_map_red(node->parent);
                _rb_tree_map_left_rotate(tree, node->parent);
                tmp = node->parent->right;
            }
            if (rb_tree_map_is_black(tmp->left) && rb_tree_map_is_black(tmp->right)) {
                rb_tree_map_red(tmp);
                node = node->parent;
            } else if (rb_tree_map_is_black(tmp->right)) {
                rb_tree_map_black(tmp->left);
                rb_tree_map_red(tmp);
                _rb_tree_map_right_rotate(tree, tmp);
                tmp = node->parent->right;
            }
            tmp->color = node->parent->color;
            rb_tree_map_black(node->parent);
            rb_tree_map_black(tmp->right);
            _rb_tree_map_left_rotate(tree, node->parent);
            node = tree->root;
        } else {
            tmp = node->parent->left;
            if (rb_tree_map_is_red(tmp)) {
                rb_tree_map_black(tmp);
                rb_tree_map_red(node->parent);
                _rb_tree_map_right_rotate(tree, node->parent);
                tmp = node->parent->left;
            }
            if (rb_tree_map_is_black(tmp->left) && rb_tree_map_is_black(tmp->right)) {
                rb_tree_map_red(tmp);
                node = node->parent;
            } else if (rb_tree_map_is_black(tmp->left)) {
                rb_tree_map_black(tmp->right);
                rb_tree_map_red(tmp);
                _rb_tree_map_left_rotate(tree, tmp);
                tmp = node->parent->left;
            }
            tmp->color = node->parent->color;
            rb_tree_map_black(node->parent);
            rb_tree_map_black(tmp->left);
            _rb_tree_map_left_rotate(tree, node->parent);
            node = tree->root;
        }
    }
    rb_tree_map_black(node);
}

void _rb_tree_map_transplant(rb_tree_map *tree, rb_tree_map_node *node, rb_tree_map_node *tmp)
{
    if (!tree) {
        return;
    }
    if (tree->root == tree->sentinel) {
        return;
    }

    if (node->parent == tree->sentinel) {
        tree->root = tmp;
    } else if (node == node->parent->left) {
        node->parent->left = tmp;
    } else {
        node->parent->right = tmp;
    }
    tmp->parent = node->parent;
}

rb_tree_map *rb_tree_map_new(rb_tree_map_cmp cmp)
{
    rb_tree_map *tree = malloc(sizeof(rb_tree_map));

    if (!tree) {
        return NULL;
    }

    rb_tree_map_node *s = _rb_tree_map_create_sentinel();
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

void rb_tree_map_insert(rb_tree_map *tree, void *key, void *value)
{
    if (!tree) {
        return;
    }
    if (tree->root == tree->sentinel) {
        rb_tree_map_node *node = _rb_tree_map_create_node(key, value, tree->sentinel);
        if (!node) {
            return;
        }
        node->parent = tree->sentinel;
        rb_tree_map_black(node);
        tree->root = node;
        tree->len++;
        return;
    }

    rb_tree_map_node *new_node = _rb_tree_map_insert_node(tree, &tree->root, tree->root, key, value, tree->cmp);
    _rb_tree_map_insert_fixup(tree, new_node);
}

void rb_tree_map_delete(rb_tree_map *tree, void *key, rb_tree_map_cb cb)
{
    if (!tree) {
        return;
    }
    if (tree->root == tree->sentinel) {
        return;
    }

    rb_tree_map_node *del_node = _rb_tree_map_find_node(tree->root, tree->sentinel, key, tree->cmp);
    if (del_node == NULL) {
        return;
    }

    rb_tree_map_node *tmp = del_node;
    rb_tree_map_color tmp_orig_color = tmp->color;
    rb_tree_map_node *rep_node = NULL;

    if (del_node->left == tree->sentinel) {
        rep_node = del_node->right;
        _rb_tree_map_transplant(tree, del_node, del_node->right);
        _rb_tree_map_free_single_node(del_node, tree->sentinel, cb);
    } else if (del_node->right == tree->sentinel) {
        rep_node = del_node->left;
        _rb_tree_map_transplant(tree, del_node, del_node->left);
        _rb_tree_map_free_single_node(del_node, tree->sentinel, cb);
    } else {
        tmp = _rb_tree_map_find_min_node(del_node->right, tree->sentinel);
        tmp_orig_color = tmp->color;
        rep_node = tmp->right;
        if (tmp->parent == del_node) {
            rep_node->parent = tmp;
        } else {
            _rb_tree_map_transplant(tree, tmp, tmp->right);
            tmp->right = del_node->right;
            tmp->right->parent = tmp;
        }
        _rb_tree_map_transplant(tree, del_node, tmp);
        tmp->left = del_node->left;
        tmp->left->parent = tmp;
        tmp->color = del_node->color;
        _rb_tree_map_free_single_node(del_node, tree->sentinel, cb);
    }
    tree->len--;
    if (tmp_orig_color == RB_TREE_MAP_BLACK) {
        _rb_tree_map_delete_fixup(tree, rep_node);
    }
}

void *rb_tree_map_search(rb_tree_map *tree, void *key)
{
    if (!tree) {
        return NULL;
    }
    if (tree->root == tree->sentinel) {
        return NULL;
    }

    rb_tree_map_node *node_found = _rb_tree_map_find_node(tree->root, tree->sentinel, key, tree->cmp);
    if (!node_found) {
        return NULL;
    }

    return node_found->value;
}

void *rb_tree_map_find_max(rb_tree_map *tree)
{
    if (!tree) {
        return NULL;
    }
    if (tree->root == tree->sentinel) {
        return NULL;
    }

    rb_tree_map_node *max_node = _rb_tree_map_find_max_node(tree->root, tree->sentinel);
    if (max_node == tree->sentinel) {
        return NULL;
    }

    return max_node->value;
}

void *rb_tree_map_find_min(rb_tree_map *tree)
{
    if (!tree) {
        return NULL;
    }
    if (tree->root == tree->sentinel) {
        return NULL;
    }

    rb_tree_map_node *min_node = _rb_tree_map_find_min_node(tree->root, tree->sentinel);
    if (min_node == tree->sentinel) {
        return NULL;
    }

    return min_node->value;
}

void rb_tree_map_traverse(rb_tree_map *tree, rb_tree_map_cb cb)
{
    if (!tree) {
        return;
    }
    if (tree->root == tree->sentinel) {
        return;
    }

    _rb_tree_map_traverse_node(tree->root, tree->sentinel, cb);
}

void rb_tree_map_free(rb_tree_map *tree, rb_tree_map_cb cb)
{
    if (!tree) {
        return;
    }
    if (tree->root == tree->sentinel) {
        free(tree->sentinel);
        free(tree);
        return;
    }

    rb_tree_map_traverse(tree, cb);
    _rb_tree_map_free_node(tree->root, tree->sentinel);

    if (tree) {
        free(tree->sentinel);
        free(tree);
    }
}
