#ifndef _sl_list_h
#define _sl_list_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>

typedef struct sl_list_node {
    void *value;
    struct sl_list_node *next;
} sl_list_node;

typedef struct sl_list {
    sl_list_node *first;
} sl_list;

typedef int(*sl_list_cmp)(void *a, void *b);

// create a new list
sl_list *sl_list_new();

// remove all the values in the list
void sl_list_clear(sl_list *list);

// destroy the list
void sl_list_destroy(sl_list *list);

// get the length of the list
int sl_list_length(sl_list *list);

// insert at the end
void sl_list_push(sl_list *list, void *value);

// insert at the beginning
void sl_list_shift(sl_list *list, void *value);

// remove the first node and return it
void *sl_list_unshift(sl_list *list);

// remove the last node and return it
void *sl_list_pop(sl_list *list);

// remove node whose value is {value}
void sl_list_remove(sl_list *list, void *value, sl_list_cmp cmp);

// check to see if value {value} exists in the list
bool sl_list_exists(sl_list *list, void *value, sl_list_cmp cmp);

// Macro usage:
// SL_LIST_FOREACH(list) {
    // your code here
    // you can use the variable "cur"
    // inside of it that references the current item of the list
// }
#define SL_LIST_FOREACH(list) sl_list_node *cur = NULL; \
    for (cur = (list)->first; cur != NULL; cur = cur->next)

#endif
