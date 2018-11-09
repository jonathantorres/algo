#ifndef _cllist_h
#define _cllist_h

typedef struct cllist_node {
    void *value;
    struct cllist_node *next;
    struct cllist_node *prev;
} cllist_node;

typedef struct cllist {
    cllist_node *first;
    cllist_node *last;
    int length;
} cllist;

typedef int(*cllist_cmp)(void *a, void *b);

// create a new list
cllist *cllist_new();

// remove all the values in the list
void cllist_clear(cllist *list);

// destroy the list
void cllist_destroy(cllist *list);

// insert at the end
void cllist_push(cllist *list, void *value);

// insert at the beginning
void cllist_shift(cllist *list, void *value);

// remove the first node and return it
void *cllist_unshift(cllist *list);

// remove the last node and return it
void *cllist_pop(cllist *list);

// remove node whose value is {value}
void cllist_remove(cllist *list, void *value, cllist_cmp cmp);

// check to see if value {value} exists in the list
int cllist_exists(cllist *list, void *value, cllist_cmp cmp);

#endif
