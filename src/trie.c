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

static void _trie_free_node(trie_node *node, trie_cb cb)
{
    array_free(node->paths, NULL);
    if (cb) {
        cb(node->value);
    }
    free(node);
}

static void _trie_free_nodes(trie_node *node, trie_cb cb)
{
    if (!node) {
        return;
    }
    trie_node *curr_node = NULL;

    for (unsigned int i = 0; i < node->paths->len; i++) {
        curr_node = array_get(node->paths, i);
        if (curr_node) {
            if (curr_node->value != NULL) { // we reached the end
                _trie_free_node(curr_node, cb);
            } else {
                _trie_free_nodes(curr_node, cb);
            }
        }
    }
}

trie *trie_new(void)
{
    trie *_trie = malloc(sizeof(trie));
    if (!_trie) {
        return NULL;
    }

    trie_node *root = _trie_create_node(NULL);
    if (!root) {
        free(_trie);
        return NULL;
    }

    _trie->root = root;

    return _trie;
}

void trie_free(trie *_trie, trie_cb cb)
{
    if (!_trie) {
        return;
    }

    _trie_free_nodes(_trie->root, cb);
    free(_trie);
}

bool trie_insert(trie *_trie, char *key, void *value)
{
    if (!_trie) {
        return false;
    }

    trie_node *root = _trie->root;
    trie_node *new_node = NULL;
    char *_key = key;

    for (unsigned int i = 0; i < strlen(_key); i++) {
        unsigned int char_index = (unsigned int)tolower((int)_key[i]) - 97; // ASCII position
        trie_node *curr_node = array_get(root->paths, char_index);
        if (curr_node) {
            root = curr_node;
        } else {
            new_node = _trie_create_node(NULL);
            if (new_node) {
                array_set(root->paths, new_node, char_index);
                root = new_node;
            } else {
                return false; // insert failed
            }
        }
    }
    root->value = value;

    return true;
}

void *trie_get(trie *_trie, char *key)
{
    if (!_trie) {
        return NULL;
    }

    trie_node *root = _trie->root;
    char *_key = key;
    for (unsigned int i = 0; i < strlen(_key); i++) {
        unsigned int char_index = (unsigned int)tolower((int)_key[i]) - 97; // ASCII position
        trie_node *curr_node = array_get(root->paths, char_index);
        if (!curr_node) {
            return NULL;
        }
        root = curr_node;
    }

    return root->value;
}
