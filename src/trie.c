#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"

#define PATHS_LENGTH 26

static void *create_node(void *value)
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

static void free_nodes(trie_node *node)
{
    trie_node *curr_node = NULL;

    for (unsigned int i = 0; i < node->paths->length; i++) {
        curr_node = array_get(node->paths, i);
        if (curr_node) {
            if (strcmp(curr_node->value, "") != 0) {
                // we reached the end
                for (unsigned int j = 0; j < curr_node->paths->length; j++) {
                    void *item = array_get(curr_node->paths, j);
                    if (item) {
                        free(item);
                    }
                }
                free(curr_node->paths);
                free(curr_node);
            } else {
                free_nodes(curr_node);
            }
        }
    }
}

void *trie_create(trie_compare cmp)
{
    trie *_trie = malloc(sizeof(trie));

    if (!_trie) {
        fputs("[trie_create] Not enough memory.", stderr);
        exit(EXIT_FAILURE);
    }

    trie_node *root = create_node("");
    if (!root) {
        free(_trie);
        fputs("[trie_create] Root node could not be created.", stderr);
        exit(EXIT_FAILURE);
    }

    _trie->root = root;
    _trie->cmp = cmp;

    return _trie;
}

void trie_destroy(trie *_trie)
{
    if (!_trie) {
        fputs("[trie_destroy] Must provide a trie.", stderr);
        exit(EXIT_FAILURE);
    }

    free_nodes(_trie->root);

    // while (root) {
    //     for (unsigned int i = 0; i < root->paths->length; i++) {
    //         curr_node = array_get(root->paths, i);
    //         if (curr_node) {
    //             root = curr_node;
    //         }
    //     }
    // }
}

unsigned int trie_insert(trie *_trie, void *key, void *value)
{
    if (!_trie) {
        fputs("[trie_insert] Must provide a trie.", stderr);
        exit(EXIT_FAILURE);
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
            new_node = create_node("");
            if (new_node) {
                array_set(root->paths, new_node, i);
                root = new_node;
            } else {
                return 1; // insert failed
            }
        }
    }
    root->value = value;

    return 0;
}
