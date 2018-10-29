#ifndef _sllist_h
#define _sllist_h

typedef struct sllist_node {
    void *value;
    struct sllist_node *next;
} sllist_node;

typedef struct sllist {
    sllist_node *first;
    int length;
} sllist;

// create a new list
sllist *sllist_new();

// remove all the values in the list
void sllist_clear(sllist *list);

// destroy the list
void sllist_destroy(sllist *list);

// insert at the end
void sllist_push(sllist *list, void *value);

// insert at the beginning
void sllist_shift(sllist *list, void *value);

// remove the first node and return it
void *sllist_unshift(sllist *list);

// remove the last node and return it
void *sllist_pop(sllist *list);

// TODO: remove node whose value is V
// (3rd parameter should be a comparison function)
// that states wheter item a or b are the same
// void sllist_remove(sllist *list, void *value);

// TODO: check to see if value V exists in the list
// (3rd parameter should be a comparison function)
// that states wheter item a or b are the same
// void sllist_exists(sllist *list, void *value);
#endif
