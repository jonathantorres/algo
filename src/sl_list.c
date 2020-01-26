#include "sl_list.h"

sl_list_node *_sl_list_create_node(void *value)
{
    sl_list_node *node = malloc(sizeof(sl_list_node));

    if (!node) {
        fputs("Not enough memory.", stderr);
        return NULL;
    }

    node->next = NULL;
    node->value = value;

    return node;
}

void _sl_list_free_node(sl_list_node *node)
{
    if (!node) {
        fputs("A valid node must be provided.", stderr);
        return;
    }

    node->next = NULL;
    node->value = NULL;

    free(node);
}

sl_list *sl_list_new()
{
    sl_list *new_list = malloc(sizeof(sl_list));

    if (!new_list) {
        fputs("Not enough memory.", stderr);
        return NULL;
    }

    new_list->first = NULL;

    return new_list;
}

void sl_list_clear(sl_list *list)
{
    if (list->first != NULL) {
        sl_list_node *current_node = list->first;
        sl_list_node *prev_node = NULL;

        while (current_node->next != NULL) {
            prev_node = current_node;
            current_node = current_node->next;

            if (prev_node) {
                _sl_list_free_node(prev_node);
            }
        }

        if (current_node) {
            _sl_list_free_node(current_node);
        }

        list->first = NULL;
    }
}

void sl_list_free(sl_list *list)
{
    if (!list) {
        fputs("Must provide a sl_list.", stderr);
        return;
    }

    sl_list_clear(list);
    free(list);
}

// get the len of the list
int sl_list_len(sl_list *list)
{
    if (!list) {
        fputs("Must provide a sl_list.", stderr);
        return -1;
    }

    int len = 0;

    if (list->first != NULL) {
        sl_list_node *current_node = list->first;
        len++;

        while (current_node->next != NULL) {
            current_node = current_node->next;
            len++;
        }
    }

    return len;
}

// insert at the end
void sl_list_push(sl_list *list, void *value)
{
    if (!list) {
        fputs("Must provide a sl_list.", stderr);
        return;
    }

    sl_list_node *new_node = _sl_list_create_node(value);

    // list is empty, this is the first element
    if (list->first == NULL) {
        list->first = new_node;
        return;
    }

    sl_list_node *current_node = list->first;

    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    current_node->next = new_node;
}

// insert at the beginning
void sl_list_shift(sl_list *list, void *value)
{
    if (!list) {
        fputs("Must provide a sl_list.", stderr);
        return;
    }

    sl_list_node *new_node = _sl_list_create_node(value);

    // list is empty, this is the first element
    if (list->first == NULL) {
        list->first = new_node;
        return;
    }

    new_node->next = list->first;
    list->first = new_node;
}

// remove the first node and return it
void *sl_list_unshift(sl_list *list)
{
    if (!list) {
        fputs("Must provide a sl_list.", stderr);
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

    sl_list_node *new_first = list->first->next;
    void *value = list->first->value;

    free(list->first);
    list->first = new_first;

    return value;
}

// remove the last node and return it
void *sl_list_pop(sl_list *list)
{
    if (!list) {
        fputs("Must provide a sl_list.", stderr);
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

        return value;
    }

    sl_list_node *current_node = list->first;
    sl_list_node *prev_node = list->first;

    while (current_node->next != NULL) {
        prev_node = current_node;
        current_node = current_node->next;
    }

    void *value = current_node->value;

    free(current_node);
    prev_node->next = NULL;

    return value;
}

// remove node whose value is {value}
void sl_list_remove(sl_list *list, void *value, sl_list_cmp cmp)
{
    if (!list) {
        fputs("Must provide a valid sl_list.", stderr);
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
            sl_list_pop(list);
        }

        return;
    }

    sl_list_node *current_node = list->first;
    sl_list_node *prev_node = list->first;

    // check the first one
    if (cmp(current_node->value, value) == 0) {
        sl_list_node *next_node = current_node->next;
        list->first = next_node;
        _sl_list_free_node(current_node);
        return;
    }

    while (current_node->next != NULL) {
        prev_node = current_node;
        current_node = current_node->next;

        if (cmp(current_node->value, value) == 0) {
            // remove the node
            prev_node->next = current_node->next;
            _sl_list_free_node(current_node);
            break;
        }
    }
}

// check to see if value {value} exists in the list
bool sl_list_exists(sl_list *list, void *value, sl_list_cmp cmp)
{
    if (!list) {
        fputs("Must provide a valid sl_list.", stderr);
        return -1;
    }

    // list is empty, not found
    if (list->first == NULL) {
        return false;
    }

    sl_list_node *current_node = list->first;

    // check the first one
    if (cmp(current_node->value, value) == 0) {
        return true;
    }

    bool found = false;

    // check the rest
    while (current_node->next != NULL) {
        current_node = current_node->next;

        if (cmp(current_node->value, value) == 0) {
            found = true;
            break;
        }
    }

    return found;
}
