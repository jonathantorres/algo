#include "cl_list.h"

cl_list_node *_cl_list_create_node(void *value)
{
    cl_list_node *node = malloc(sizeof(cl_list_node));

    if (!node) {
        return NULL;
    }

    node->prev = NULL;
    node->next = NULL;
    node->value = value;

    return node;
}

void _cl_list_free_node(cl_list_node *node, cl_list_free_cb cb)
{
    if (!node) {
        return;
    }
    if (cb) {
        cb(node->value);
    }

    node->prev = NULL;
    node->next = NULL;
    node->value = NULL;

    free(node);
}

// create a new list
cl_list *cl_list_new()
{
    cl_list *new_list = malloc(sizeof(cl_list));

    if (!new_list) {
        return NULL;
    }

    new_list->first = NULL;
    new_list->last = NULL;

    return new_list;
}

// remove all the values in the list
void cl_list_clear(cl_list *list, cl_list_free_cb cb)
{
    if (list->first != NULL) {
        cl_list_node *current_node = list->first;

        while (current_node != list->last) {
            current_node = current_node->next;

            if (current_node->prev) {
                _cl_list_free_node(current_node->prev, cb);
            }
        }

        if (current_node) {
            _cl_list_free_node(current_node, cb);
        }

        list->first = NULL;
        list->last = NULL;
    }
}

// destroy the list
void cl_list_free(cl_list *list, cl_list_free_cb cb)
{
    if (!list) {
        return;
    }

    cl_list_clear(list, cb);
    free(list);
}

// get the len of the list
int cl_list_len(cl_list *list)
{
    if (!list) {
        return -1;
    }

    int len = 0;
    if (list->first != NULL) {
        cl_list_node *current_node = list->first;
        len++;

        while (current_node != list->last) {
            current_node = current_node->next;
            len++;
        }
    }

    return len;
}

// insert at the end
void cl_list_push(cl_list *list, void *value)
{
    if (!list) {
        return;
    }

    cl_list_node *new_node = _cl_list_create_node(value);

    // list is empty, this is the first element
    if (list->first == NULL) {
        list->first = new_node;
        list->last = new_node;
        return;
    }

    cl_list_node *current_node = list->first;

    while (current_node != list->last) {
        current_node = current_node->next;
    }

    new_node->prev = current_node;
    new_node->next = list->first;
    current_node->next = new_node;
    list->last = new_node;
}

// insert at the beginning
void cl_list_shift(cl_list *list, void *value)
{
    if (!list) {
        return;
    }

    cl_list_node *new_node = _cl_list_create_node(value);

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
void *cl_list_unshift(cl_list *list)
{
    if (!list) {
        return NULL;
    }

    // list is empty, return nothing
    if (list->first == NULL) {
        return NULL;
    }

    // list has just 1 node
    if (list->first == list->last) {
        void *value = list->first->value;
        _cl_list_free_node(list->first, NULL);

        list->first = NULL;
        list->last = NULL;

        return value;
    }

    cl_list_node *new_first = list->first->next;
    void *value = list->first->value;

    _cl_list_free_node(list->first, NULL);
    new_first->prev = list->last;
    list->first = new_first;

    return value;
}

// remove the last node and return it
void *cl_list_pop(cl_list *list)
{
    if (!list) {
        return NULL;
    }

    // list is empty, return nothing
    if (list->first == NULL) {
        return NULL;
    }

    // list has just 1 node
    if (list->first == list->last) {
        void *value = list->first->value;
        _cl_list_free_node(list->first, NULL);
        list->first = NULL;
        list->last = NULL;

        return value;
    }

    cl_list_node *current_node = list->first;

    while (current_node != list->last) {
        current_node = current_node->next;
    }

    void *value = current_node->value;
    current_node->prev->next = list->first;
    list->last = current_node->prev;
    _cl_list_free_node(current_node, NULL);

    return value;
}

// remove node whose value is {value}
void cl_list_remove(cl_list *list, void *value, cl_list_cmp cmp, cl_list_free_cb cb)
{
    if (!list) {
        return;
    }

    // list is empty, return nothing
    if (list->first == NULL) {
        return;
    }

    // list has just 1 node
    if (list->first == list->last) {
        void *node_value = list->first->value;

        if (cmp(node_value, value) == 0) {
            _cl_list_free_node(list->first, cb);
        }

        return;
    }

    cl_list_node *current_node = list->first;

    // check the first one
    if (cmp(current_node->value, value) == 0) {
        cl_list_node *next_node = current_node->next;
        next_node->prev = list->last;
        list->first = next_node;
        _cl_list_free_node(current_node, cb);
        return;
    }

    while (current_node != list->last) {
        current_node = current_node->next;

        if (cmp(current_node->value, value) == 0) {
            // remove the node
            current_node->prev->next = current_node->next;
            current_node->next->prev = current_node->prev;
            _cl_list_free_node(current_node, cb);
            break;
        }
    }
}

// check to see if value {value} exists in the list
bool cl_list_exists(cl_list *list, void *value, cl_list_cmp cmp)
{
    if (!list) {
        return -1;
    }

    // list is empty, not found
    if (list->first == NULL) {
        return false;
    }

    cl_list_node *current_node = list->first;

    // check the first one
    if (cmp(current_node->value, value) == 0) {
        return true;
    }

    bool found = false;
    // check the rest
    while (current_node != list->last) {
        current_node = current_node->next;

        if (cmp(current_node->value, value) == 0) {
            found = true;
            break;
        }
    }

    return found;
}
