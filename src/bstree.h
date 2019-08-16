#ifndef _bstree_h
#define _bstree_h

typedef int (*bstree_compare) (void *a, void *b);

typedef struct bstree_node {
    void *key;
    void *value;
    struct bstree_node *left;
    struct bstree_node *right;
    struct bstree_node *parent;
} bstree_node;

typedef struct bstree {
    int count;
    bstree_compare compare;
    bstree_node *root;
} bstree;

typedef int (*bstree_traverse_cb) (bstree_node *node);

bstree *bstree_create(bstree_compare compare);
void bstree_destroy(bstree *tree);
int bstree_set(bstree *tree, void *key, void *value);
void *bstree_get(bstree *tree, void *key);
int bstree_traverse(bstree *tree, bstree_traverse_cb traverse_cb);
void *bstree_delete(bstree *tree, void *key);

#endif
