#ifndef _dllist_h
#define _dllist_h

typedef struct dllist_node {
    void *value;
    struct dllist_node *next;
    struct dllist_node *prev;
} dllist_node;

typedef struct dllist {
    dllist_node *first;
    int length;
} dllist;

// create a new list
dllist *dllist_new();

// remove all the values in the list
void dllist_clear(dllist *list);

// destroy the list
void dllist_destroy(dllist *list);

// insert at the end
void dllist_push(dllist *list, void *value);

// insert at the beginning
void dllist_shift(dllist *list, void *value);

// remove the first node and return it
void *dllist_unshift(dllist *list);

// remove the last node and return it
void *dllist_pop(dllist *list);

#endif
