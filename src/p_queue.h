#ifndef _p_queue_h
#define _p_queue_h

#include "bs_tree.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct p_queue {
    bs_tree *tree;
} p_queue;

typedef int (*p_queue_cmp)(void *a, void *b);
typedef void (*p_queue_cb)(bs_tree_node *node);

p_queue *p_queue_new(p_queue_cmp cmp);
void p_queue_insert(p_queue *queue, void *value);
void *p_queue_find_min(p_queue *queue);
void *p_queue_delete_min(p_queue *queue, p_queue_cb cb);
int p_queue_len(p_queue *queue);
void p_queue_traverse(p_queue *queue, p_queue_cb cb);
void p_queue_free(p_queue *queue, p_queue_cb cb);

#endif
