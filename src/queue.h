#ifndef _queue_h
#define _queue_h

#include "dllist.h"

typedef dllist queue;

queue *queue_new();
void queue_destroy(queue *_queue);
void queue_clear(queue *_queue);
void queue_enqueue(queue *_queue, void *value);
void *queue_dequeue(queue *_queue);
void *queue_peek(queue *_queue);
int queue_length(queue *_queue);

// Macro usage:
// QUEUE_FOREACH(queue) {
    // your code here
    // you can use the variable "cur"
    // inside of it that references the current item of the queue
// }
#define QUEUE_FOREACH(queue) dllist_node *cur = NULL; \
    for (cur = (queue)->first; cur != NULL; cur = cur->next)

#endif
