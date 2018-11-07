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
