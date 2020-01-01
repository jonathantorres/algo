#include "queue.h"

queue *queue_new()
{
    return dl_list_new();
}

void queue_enqueue(queue *_queue, void *value)
{
    if (!_queue) {
        fputs("Must provide a valid queue.", stderr);
        return;
    }

    dl_list_push(_queue, value);
}

void *queue_dequeue(queue *_queue)
{
    if (!_queue) {
        fputs("Must provide a valid queue.", stderr);
        return NULL;
    }

    return dl_list_unshift(_queue);
}

void *queue_peek(queue *_queue)
{
    if (!_queue) {
        fputs("Must provide a valid queue.", stderr);
        return NULL;
    }

    if (_queue->first == NULL) {
        fputs("The queue is empty", stderr);
        return NULL;
    }

    return _queue->first->value;
}

void queue_destroy(queue *_queue)
{
    if (!_queue) {
        fputs("Must provide a valid queue.", stderr);
        return;
    }

    dl_list_destroy(_queue);
}

void queue_clear(queue *_queue)
{
    if (!_queue) {
        fputs("Must provide a valid queue.", stderr);
        return;
    }

    dl_list_clear(_queue);
}

int queue_length(queue *_queue)
{
    if (!_queue) {
        fputs("Must provide a valid queue.", stderr);
        return 0;
    }

    return dl_list_length(_queue);
}
