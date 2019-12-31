#ifndef _dl_list_h
#define _dl_list_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct dl_list_node {
    void *value;
    struct dl_list_node *next;
    struct dl_list_node *prev;
} dl_list_node;

typedef struct dl_list {
    dl_list_node *first;
} dl_list;

typedef int(*dl_list_cmp)(void *a, void *b);

// create a new list
dl_list *dl_list_new();

// remove all the values in the list
void dl_list_clear(dl_list *list);

// destroy the list
void dl_list_destroy(dl_list *list);

// get the length of the list
int dl_list_length(dl_list *list);

// insert at the end
void dl_list_push(dl_list *list, void *value);

// insert at the beginning
void dl_list_shift(dl_list *list, void *value);

// remove the first node and return it
void *dl_list_unshift(dl_list *list);

// remove the last node and return it
void *dl_list_pop(dl_list *list);

// remove node whose value is {value}
void dl_list_remove(dl_list *list, void *value, dl_list_cmp cmp);

// check to see if value {value} exists in the list
bool dl_list_exists(dl_list *list, void *value, dl_list_cmp cmp);

// Macro usage:
// DL_LIST_FOREACH(list) {
    // your code here
    // you can use the variable "cur"
    // inside of it that references the current item of the list
// }
#define DL_LIST_FOREACH(list) dl_list_node *cur = NULL; \
    for (cur = (list)->first; cur != NULL; cur = cur->next)

#endif
