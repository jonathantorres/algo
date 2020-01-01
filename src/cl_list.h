#ifndef _cl_list_h
#define _cl_list_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct cl_list_node {
    void *value;
    struct cl_list_node *next;
    struct cl_list_node *prev;
} cl_list_node;

typedef struct cl_list {
    cl_list_node *first;
    cl_list_node *last;
} cl_list;

typedef int(*cl_list_cmp)(void *a, void *b);

// create a new list
cl_list *cl_list_new();

// remove all the values in the list
void cl_list_clear(cl_list *list);

// destroy the list
void cl_list_destroy(cl_list *list);

// get the length of the list
int cl_list_length(cl_list *list);

// insert at the end
void cl_list_push(cl_list *list, void *value);

// insert at the beginning
void cl_list_shift(cl_list *list, void *value);

// remove the first node and return it
void *cl_list_unshift(cl_list *list);

// remove the last node and return it
void *cl_list_pop(cl_list *list);

// remove node whose value is {value}
void cl_list_remove(cl_list *list, void *value, cl_list_cmp cmp);

// check to see if value {value} exists in the list
bool cl_list_exists(cl_list *list, void *value, cl_list_cmp cmp);

// Macro usage:
// CL_LIST_FOREACH(list) {
    // your code here
    // you can use the variable "cur"
    // inside of it that references the current item of the list
// }
#define CL_LIST_FOREACH(list) \
    for (cl_list_node *cur = (list)->first; cur != NULL && !(cur == (list)->last); cur = cur->next)

#endif
