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
typedef void(*cl_list_free_cb)(void *value);

cl_list *cl_list_new();
void cl_list_clear(cl_list *list, cl_list_free_cb cb);
void cl_list_free(cl_list *list, cl_list_free_cb cb);
int cl_list_len(cl_list *list);
void cl_list_push(cl_list *list, void *value);
void cl_list_shift(cl_list *list, void *value);
void *cl_list_unshift(cl_list *list);
void *cl_list_pop(cl_list *list);
void cl_list_remove(cl_list *list, void *value, cl_list_cmp cmp, cl_list_free_cb cb);
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
