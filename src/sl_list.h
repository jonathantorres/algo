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
typedef void(*sl_list_free_cb)(void *value);

sl_list *sl_list_new();
void sl_list_clear(sl_list *list, sl_list_free_cb cb);
void sl_list_free(sl_list *list, sl_list_free_cb cb);
int sl_list_len(sl_list *list);
void sl_list_push(sl_list *list, void *value);
void sl_list_shift(sl_list *list, void *value);
void *sl_list_unshift(sl_list *list);
void *sl_list_pop(sl_list *list);
void sl_list_remove(sl_list *list, void *value, sl_list_cmp cmp, sl_list_free_cb cb);
bool sl_list_exists(sl_list *list, void *value, sl_list_cmp cmp);

// Macro usage:
// SL_LIST_FOREACH(list) {
    // your code here
    // you can use the variable "cur"
    // inside of it that references the current item of the list
// }
#define SL_LIST_FOREACH(list) \
    for (sl_list_node *cur = (list)->first; cur != NULL; cur = cur->next)

#endif
