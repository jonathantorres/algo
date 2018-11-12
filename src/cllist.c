#include "cllist.h"
#include <stdio.h>
#include <stdlib.h>

cllist_node *create_node(void *value)
{
    cllist_node *node = malloc(sizeof(cllist_node));

    if (!node) {
        fputs("Not enough memory.", stderr);
        exit(EXIT_FAILURE);
    }

    node->prev = NULL;
    node->next = NULL;
    node->value = value;

    return node;
}

void destroy_node(cllist_node *node)
{
    if (!node) {
        fputs("A valid node must be provided.", stderr);
        exit(EXIT_FAILURE);
    }

    node->prev = NULL;
    node->next = NULL;
    node->value = NULL;

    free(node);

    node = NULL;
}

// create a new list
cllist *cllist_new()
{
    cllist *new_list = malloc(sizeof(cllist));

    if (!new_list) {
        fputs("Not enough memory.", stderr);
        exit(EXIT_FAILURE);
    }

    new_list->length = 0;
    new_list->first = NULL;
    new_list->last = NULL;

    return new_list;
}

// remove all the values in the list
void cllist_clear(cllist *list)
{
    if (list->first != NULL) {
        cllist_node *current_node = list->first;

        while (current_node != list->last) {
            current_node = current_node->next;

            if (current_node->prev) {
                destroy_node(current_node->prev);
                list->length--;
            }
        }

        if (current_node) {
            destroy_node(current_node);
            list->length--;
        }

        list->first = NULL;
        list->last = NULL;
    }
}

// destroy the list
void cllist_destroy(cllist *list)
{
    if (!list) {
        fputs("Must provide a cllist.", stderr);
        exit(EXIT_FAILURE);
    }

    cllist_clear(list);

    free(list);

    list = NULL;
}

// insert at the end
void cllist_push(cllist *list, void *value)
{
    if (!list) {
        fputs("Must provide a cllist.", stderr);
        exit(EXIT_FAILURE);
    }

    cllist_node *new_node = create_node(value);
    list->length++;

    // list is empty, this is the first element
    if (list->first == NULL) {
        list->first = new_node;
        list->last = new_node;
        return;
    }

    cllist_node *current_node = list->first;

    while (current_node != list->last) {
        current_node = current_node->next;
    }

    new_node->prev = current_node;
    new_node->next = list->first;
    current_node->next = new_node;
    list->last = new_node;
}

// insert at the beginning
void cllist_shift(cllist *list, void *value)
{
    if (!list) {
        fputs("Must provide a cllist.", stderr);
        exit(EXIT_FAILURE);
    }

    cllist_node *new_node = create_node(value);
    list->length++;

    // list is empty, this is the first element
    if (list->first == NULL) {
        list->first = new_node;
        list->last = new_node;
        return;
    }

    new_node->next = list->first;
    list->first = new_node;
}

// remove the first node and return it
void *cllist_unshift(cllist *list)
{
    if (!list) {
        fputs("Must provide a cllist.", stderr);
        exit(EXIT_FAILURE);
    }

    // list is empty, return nothing
    if (list->first == NULL) {
        return NULL;
    }

    list->length--;

    // list has just 1 node
    if (list->first == list->last) {
        void *value = list->first->value;
        destroy_node(list->first);

        list->first = NULL;
        list->last = NULL;

        return value;
    }

    cllist_node *new_first = list->first->next;
    void *value = list->first->value;

    destroy_node(list->first);
    new_first->prev = list->last;
    list->first = new_first;

    return value;
}

// remove the last node and return it
void *cllist_pop(cllist *list)
{
    if (!list) {
        fputs("Must provide a cllist.", stderr);
        exit(EXIT_FAILURE);
    }

    // list is empty, return nothing
    if (list->first == NULL) {
        return NULL;
    }

    list->length--;

    // list has just 1 node
    if (list->first == list->last) {
        void *value = list->first->value;
        destroy_node(list->first);
        list->first = NULL;
        list->last = NULL;

        return value;
    }

    cllist_node *current_node = list->first;

    while (current_node != list->last) {
        current_node = current_node->next;
    }

    void *value = current_node->value;
    current_node->prev->next = list->first;
    list->last = current_node->prev;
    destroy_node(current_node);
    current_node = NULL;

    return value;
}

// remove node whose value is {value}
void cllist_remove(cllist *list, void *value, cllist_cmp cmp)
{
    if (!list) {
        fputs("Must provide a valid cllist.", stderr);
        exit(EXIT_FAILURE);
    }

    // list is empty, return nothing
    if (list->first == NULL) {
        return;
    }

    // list has just 1 node
    if (list->first == list->last) {
        void *node_value = list->first->value;

        if (cmp(node_value, value) == 0) {
            cllist_pop(list);
        }

        return;
    }

    cllist_node *current_node = list->first;

    // check the first one
    if (cmp(current_node->value, value) == 0) {
        cllist_node *next_node = current_node->next;
        next_node->prev = list->last;
        list->first = next_node;
        destroy_node(current_node);
        list->length--;
        return;
    }

    while (current_node != list->last) {
        current_node = current_node->next;

        if (cmp(current_node->value, value) == 0) {
            // remove the node
            current_node->prev->next = current_node->next;
            current_node->next->prev = current_node->prev;
            destroy_node(current_node);
            list->length--;
            break;
        }
    }
}

// check to see if value {value} exists in the list
int cllist_exists(cllist *list, void *value, cllist_cmp cmp)
{
    if (!list) {
        fputs("Must provide a valid cllist.", stderr);
        exit(EXIT_FAILURE);
    }

    // list is empty, not found
    if (list->first == NULL) {
        return 0;
    }

    cllist_node *current_node = list->first;

    // check the first one
    if (cmp(current_node->value, value) == 0) {
        return 1;
    }

    int found = 0;

    // check the rest
    while (current_node != list->last) {
        current_node = current_node->next;

        if (cmp(current_node->value, value) == 0) {
            found = 1;
            break;
        }
    }

    return found;
}
