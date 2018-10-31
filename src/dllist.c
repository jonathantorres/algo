#include "dllist.h"
#include <stdio.h>
#include <stdlib.h>

dllist_node *create_node(void *value)
{
    dllist_node *node = malloc(sizeof(dllist_node));

    if (!node) {
        fputs("Not enough memory.", stderr);
        exit(EXIT_FAILURE);
    }

    node->prev = NULL;
    node->next = NULL;
    node->value = value;

    return node;
}

void destroy_node(dllist_node *node)
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

dllist *dllist_new()
{
    dllist *new_list = malloc(sizeof(dllist));

    if (!new_list) {
        fputs("Not enough memory.", stderr);
        exit(EXIT_FAILURE);
    }

    new_list->length = 0;
    new_list->first = NULL;

    return new_list;
}

// TODO: use list->prev here, to simply this code
void dllist_clear(dllist *list)
{
    if (list->first != NULL) {
        dllist_node *current_node = list->first;
        dllist_node *prev_node = NULL;

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

void dllist_destroy(dllist *list)
{
    if (!list) {
        fputs("Must provide a dllist.", stderr);
        exit(EXIT_FAILURE);
    }

    dllist_clear(list);

    free(list);

    list = NULL;
}

// insert at the end
// void dllist_push(dllist *list, void *value)
// {
//     if (!list) {
//         fputs("Must provide a dllist.", stderr);
//         exit(EXIT_FAILURE);
//     }

//     dllist_node *new_node = create_node(value);
//     list->length++;

//     // list is empty, this is the first element
//     if (list->first == NULL) {
//         list->first = new_node;
//         return;
//     }

//     dllist_node *current_node = list->first;

//     while (current_node->next != NULL) {
//         current_node = current_node->next;
//     }

//     current_node->next = new_node;
// }

// insert at the beginning
// void dllist_shift(dllist *list, void *value)
// {
//     if (!list) {
//         fputs("Must provide a dllist.", stderr);
//         exit(EXIT_FAILURE);
//     }

//     dllist_node *new_node = create_node(value);
//     list->length++;

//     // list is empty, this is the first element
//     if (list->first == NULL) {
//         list->first = new_node;
//         return;
//     }

//     new_node->next = list->first;
//     list->first = new_node;
// }

// remove the first node and return it
// void *dllist_unshift(dllist *list)
// {
//     if (!list) {
//         fputs("Must provide a dllist.", stderr);
//         exit(EXIT_FAILURE);
//     }

//     // list is empty, return nothing
//     if (list->first == NULL) {
//         return NULL;
//     }

//     list->length--;

//     // list has just 1 node
//     if (list->first->next == NULL) {
//         void *value = list->first->value;
//         free(list->first);
//         list->first = NULL;

//         return value;
//     }

//     dllist_node *new_first = list->first->next;
//     void *value = list->first->value;

//     free(list->first);
//     list->first = new_first;

//     return value;
// }

// remove the last node and return it
// void *dllist_pop(dllist *list)
// {
//     if (!list) {
//         fputs("Must provide a dllist.", stderr);
//         exit(EXIT_FAILURE);
//     }

//     // list is empty, return nothing
//     if (list->first == NULL) {
//         return NULL;
//     }

//     list->length--;

//     // list has just 1 node
//     if (list->first->next == NULL) {
//         void *value = list->first->value;
//         free(list->first);
//         list->first = NULL;

//         return value;
//     }

//     dllist_node *current_node = list->first;
//     dllist_node *prev_node = list->first;

//     while (current_node->next != NULL) {
//         prev_node = current_node;
//         current_node = current_node->next;
//     }

//     void *value = current_node->value;

//     free(current_node);
//     current_node = NULL;
//     prev_node->next = NULL;

//     return value;
// }
