#include "sllist.h"
#include <stdio.h>
#include <stdlib.h>

sllist_node *create_node(void *value)
{
    sllist_node *node = malloc(sizeof(sllist_node));

    if (!node) {
        fputs("Not enough memory.", stderr);
        return NULL;
    }

    node->next = NULL;
    node->value = value;

    return node;
}

void destroy_node(sllist_node *node)
{
    if (!node) {
        fputs("A valid node must be provided.", stderr);
        return;
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
        return NULL;
    }

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
            }
        }

        if (current_node) {
            destroy_node(current_node);
        }

        list->first = NULL;
    }
}

void sllist_destroy(sllist *list)
{
    if (!list) {
        fputs("Must provide a sllist.", stderr);
        return;
    }

    sllist_clear(list);
    free(list);
    list = NULL;
}

// get the length of the list
int sllist_length(sllist *list)
{
    if (!list) {
        fputs("Must provide a sllist.", stderr);
        return -1;
    }

    int length = 0;

    if (list->first != NULL) {
        sllist_node *current_node = list->first;
        sllist_node *prev_node = NULL;
        length++;

        while (current_node->next != NULL) {
            prev_node = current_node;
            current_node = current_node->next;
            length++;
        }
    }

    return length;
}

// insert at the end
void sllist_push(sllist *list, void *value)
{
    if (!list) {
        fputs("Must provide a sllist.", stderr);
        return;
    }

    sllist_node *new_node = create_node(value);

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
        return;
    }

    sllist_node *new_node = create_node(value);

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
        return NULL;
    }

    // list is empty, return nothing
    if (list->first == NULL) {
        return NULL;
    }

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
        return NULL;
    }

    // list is empty, return nothing
    if (list->first == NULL) {
        return NULL;
    }

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

// remove node whose value is {value}
void sllist_remove(sllist *list, void *value, sllist_cmp cmp)
{
    if (!list) {
        fputs("Must provide a valid sllist.", stderr);
        return;
    }

    // list is empty, return nothing
    if (list->first == NULL) {
        return;
    }

    // list has just 1 node
    if (list->first->next == NULL) {
        void *node_value = list->first->value;

        if (cmp(node_value, value) == 0) {
            sllist_pop(list);
        }

        return;
    }

    sllist_node *current_node = list->first;
    sllist_node *prev_node = list->first;

    // check the first one
    if (cmp(current_node->value, value) == 0) {
        sllist_node *next_node = current_node->next;
        list->first = next_node;
        destroy_node(current_node);
        return;
    }

    while (current_node->next != NULL) {
        prev_node = current_node;
        current_node = current_node->next;

        if (cmp(current_node->value, value) == 0) {
            // remove the node
            prev_node->next = current_node->next;
            destroy_node(current_node);
            break;
        }
    }
}

// check to see if value {value} exists in the list
int sllist_exists(sllist *list, void *value, sllist_cmp cmp)
{
    if (!list) {
        fputs("Must provide a valid sllist.", stderr);
        return -1;
    }

    // list is empty, not found
    if (list->first == NULL) {
        return 0;
    }

    sllist_node *current_node = list->first;
    sllist_node *prev_node = list->first;

    // check the first one
    if (cmp(current_node->value, value) == 0) {
        return 1;
    }

    int found = 0;

    // check the rest
    while (current_node->next != NULL) {
        prev_node = current_node;
        current_node = current_node->next;

        if (cmp(current_node->value, value) == 0) {
            found = 1;
            break;
        }
    }

    return found;
}
