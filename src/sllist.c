#include "sllist.h"
#include <stdio.h>
#include <stdlib.h>

sllist_node *create_node(void *value)
{
    sllist_node *node = malloc(sizeof(sllist_node));

    if (!node) {
        fputs("Not enough memory.", stderr);
        exit(EXIT_FAILURE);
    }

    node->next = NULL;
    node->value = value;

    return node;
}

void destroy_node(sllist_node *node)
{
    if (!node) {
        fputs("A valid node must be provided.", stderr);
        exit(EXIT_FAILURE);
    }

    node->next = NULL;
    node->value = NULL;

    free(node);

    node = NULL;
}

sllist *sllist_new()
{
    sllist *new_list = malloc(sizeof(sllist));

    if (!new_list) {
        fputs("Not enough memory.", stderr);
        exit(EXIT_FAILURE);
    }

    new_list->length = 0;
    new_list->first = NULL;

    return new_list;
}

void sllist_clear(sllist *list)
{
    if (list->first != NULL) {
        sllist_node *current_node = list->first;
        sllist_node *prev_node = NULL;

        while (current_node->next != NULL) {
            prev_node = current_node;
            current_node = current_node->next;

            if (prev_node) {
                destroy_node(prev_node);
                list->length--;
            }
        }

        if (current_node) {
            destroy_node(current_node);
            list->length--;
        }

        list->first = NULL;
    }
}

void sllist_destroy(sllist *list)
{
    if (!list) {
        fputs("Must provide a sllist.", stderr);
        exit(EXIT_FAILURE);
    }

    sllist_clear(list);

    free(list);

    list = NULL;
}

// insert at the end
void sllist_push(sllist *list, void *value)
{
    if (!list) {
        fputs("Must provide a sllist.", stderr);
        exit(EXIT_FAILURE);
    }

    sllist_node *new_node = create_node(value);
    list->length++;

    // list is empty, this is the first element
    if (list->first == NULL) {
        list->first = new_node;
        return;
    }

    sllist_node *current_node = list->first;

    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    current_node->next = new_node;
}

// insert at the beginning
void sllist_shift(sllist *list, void *value)
{
    if (!list) {
        fputs("Must provide a sllist.", stderr);
        exit(EXIT_FAILURE);
    }

    sllist_node *new_node = create_node(value);
    list->length++;

    // list is empty, this is the first element
    if (list->first == NULL) {
        list->first = new_node;
        return;
    }

    new_node->next = list->first;
    list->first = new_node;
}

// remove the first node and return it
void *sllist_unshift(sllist *list)
{
    if (!list) {
        fputs("Must provide a sllist.", stderr);
        exit(EXIT_FAILURE);
    }

    // list is empty, return nothing
    if (list->first == NULL) {
        return NULL;
    }

    list->length--;

    // list has just 1 node
    if (list->first->next == NULL) {
        void *value = list->first->value;
        free(list->first);
        list->first = NULL;

        return value;
    }

    sllist_node *new_first = list->first->next;
    void *value = list->first->value;

    free(list->first);
    list->first = new_first;

    return value;
}

// remove the last node and return it
void *sllist_pop(sllist *list)
{
    if (!list) {
        fputs("Must provide a sllist.", stderr);
        exit(EXIT_FAILURE);
    }

    // list is empty, return nothing
    if (list->first == NULL) {
        return NULL;
    }

    list->length--;

    // list has just 1 node
    if (list->first->next == NULL) {
        void *value = list->first->value;
        free(list->first);
        list->first = NULL;

        return value;
    }

    sllist_node *current_node = list->first;
    sllist_node *prev_node = list->first;

    while (current_node->next != NULL) {
        prev_node = current_node;
        current_node = current_node->next;
    }

    void *value = current_node->value;

    free(current_node);
    current_node = NULL;
    prev_node->next = NULL;

    return value;
}
