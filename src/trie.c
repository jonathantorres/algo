#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "trie.h"

#define PATHS_LENGTH 26

static void *_trie_create_node(void *value)
{
    trie_node *node = malloc(sizeof(trie_node));
    if (!node) {
        return NULL;
    }

    array *paths = array_create(PATHS_LENGTH, sizeof(trie_node*));
    if (!paths) {
        free(node);
        return NULL;
    }

    paths->length = paths->capacity;
    node->value = value;
    node->paths = paths;

    return node;
}

static void _trie_free_node(trie_node *node)
{
    // for (unsigned int i = 0; i < node->paths->length; i++) {
    //     void *item = array_get(node->paths, i);
    //     if (item) {
    //         free(item);
    //     }
    // }
    // free(node->paths);
    array_destroy(node->paths);
    free(node);
}

static void _trie_free_nodes(trie_node *node)
{
    trie_node *curr_node = NULL;

    for (unsigned int i = 0; i < node->paths->length; i++) {
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

void *trie_create(trie_compare cmp)
{
    trie *_trie = malloc(sizeof(trie));

    if (!_trie) {
        fputs("[trie_create] Not enough memory.", stderr);
        return NULL;
    }

    trie_node *root = _trie_create_node("");
    if (!root) {
        free(_trie);
        fputs("[trie_create] Root node could not be created.", stderr);
        return NULL;
    }

    _trie->root = root;
    _trie->cmp = cmp;

    return _trie;
}

void trie_destroy(trie *_trie)
{
    if (!_trie) {
        fputs("[trie_destroy] Must provide a trie.", stderr);
        return;
    }

    _trie_free_nodes(_trie->root);
    free(_trie);
}

bool trie_insert(trie *_trie, void *key, void *value)
{
    if (!_trie) {
        fputs("[trie_insert] Must provide a trie.", stderr);
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
