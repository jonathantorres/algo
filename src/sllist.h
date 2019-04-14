#ifndef _sllist_h
#define _sllist_h

#include <stdbool.h>

typedef struct sllist_node {
    void *value;
    struct sllist_node *next;
} sllist_node;

typedef struct sllist {
    sllist_node *first;
} sllist;

typedef int(*sllist_cmp)(void *a, void *b);

// create a new list
sllist *sllist_new();

// remove all the values in the list
void sllist_clear(sllist *list);

// destroy the list
void sllist_destroy(sllist *list);

// get the length of the list
int sllist_length(sllist *list);

// insert at the end
void sllist_push(sllist *list, void *value);

// insert at the beginning
void sllist_shift(sllist *list, void *value);

// remove the first node and return it
void *sllist_unshift(sllist *list);

// remove the last node and return it
void *sllist_pop(sllist *list);

// remove node whose value is {value}
void sllist_remove(sllist *list, void *value, sllist_cmp cmp);

// check to see if value {value} exists in the list
bool sllist_exists(sllist *list, void *value, sllist_cmp cmp);

// Macro usage:
// SLLIST_FOREACH(list) {
    // your code here
    // you can use the variable "cur"
    // inside of it that references the current item of the list
// }
#define SLLIST_FOREACH(list) sllist_node *cur = NULL; \
    for (cur = (list)->first; cur != NULL; cur = cur->next)

#endif
