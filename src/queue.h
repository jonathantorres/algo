#ifndef _queue_h
#define _queue_h

#include <stdio.h>
#include <stdlib.h>
#include "dl_list.h"

typedef dl_list queue;

queue *queue_new();
void queue_free(queue *_queue);
void queue_clear(queue *_queue);
void queue_enqueue(queue *_queue, void *value);
void *queue_dequeue(queue *_queue);
void *queue_peek(queue *_queue);
int queue_len(queue *_queue);

// Macro usage:
// QUEUE_FOREACH(queue) {
    // your code here
    // you can use the variable "cur"
    // inside of it that references the current item of the queue
// }
#define QUEUE_FOREACH(queue) \
    for (dl_list_node *cur = (queue)->first; cur != NULL; cur = cur->next)

#endif
