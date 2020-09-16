#include "trie.h"

#define PATHS_LEN 26

static void *_trie_create_node(void *value)
{
    trie_node *node = malloc(sizeof(trie_node));
    if (!node) {
        return NULL;
    }

    array *paths = array_new(PATHS_LEN, sizeof(trie_node*));
    if (!paths) {
        free(node);
        return NULL;
    }

    paths->len = paths->capacity;
    node->value = value;
    node->paths = paths;

    return node;
}

static void _trie_free_node(trie_node *node)
{
    // for (unsigned int i = 0; i < node->paths->len; i++) {
    //     void *item = array_get(node->paths, i);
    //     if (item) {
    //         free(item);
    //     }
    // }
    // free(node->paths);
    array_free(node->paths, NULL);
    free(node);
}

static void _trie_free_nodes(trie_node *node)
{
    trie_node *curr_node = NULL;

    for (unsigned int i = 0; i < node->paths->len; i++) {
        curr_node = array_get(node->paths, i);
        if (curr_node) {
            // we reached the end
            if (strcmp(curr_node->value, "") != 0) {
                _trie_free_node(curr_node);
            } else {
                _trie_free_nodes(curr_node);
            }
        }
    }
}

void *trie_new(trie_cmp cmp)
{
    trie *_trie = malloc(sizeof(trie));
    if (!_trie) {
        return NULL;
    }

    trie_node *root = _trie_create_node("");
    if (!root) {
        free(_trie);
        return NULL;
    }

    _trie->root = root;
    _trie->cmp = cmp;

    return _trie;
}

void trie_free(trie *_trie)
{
    if (!_trie) {
        return;
    }

    _trie_free_nodes(_trie->root);
    free(_trie);
}

bool trie_insert(trie *_trie, void *key, void *value)
{
    if (!_trie) {
        return false;
    }

    trie_node *root = _trie->root;
    trie_node *new_node = NULL;
    char *_key = key;

    for (unsigned int i = 0; i < strlen(_key); i++) {
        unsigned int char_index = (unsigned int)_key[i] - 97; // ASCII position
        trie_node *curr_node = array_get(root->paths, char_index);
        if (curr_node) {
            root = curr_node;
        } else {
            new_node = _trie_create_node("");
            if (new_node) {
                array_set(root->paths, new_node, i);
                root = new_node;
            } else {
                return false; // insert failed
            }
        }
    }
    root->value = value;

    return true;
}
