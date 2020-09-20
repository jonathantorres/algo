#include "heap_sort.h"

void p_queue_int_free_cb(void *value)
{
    if (value) {
        // nothing to do here
    }
}

p_queue *make_heap(array *_array, cmp_f cmp)
{
    p_queue *queue = p_queue_new(cmp);
    if (!queue) {
        return NULL;
    }
    for (unsigned int i = 0; i < _array->len; i++) {
        p_queue_insert(queue, array_get(_array, i));
    }
    return queue;
}

void heap_sort(array *_array, cmp_f cmp)
{
    if (!_array) {
        return;
    }
    p_queue *queue = make_heap(_array, cmp);
    if (!queue) {
        return;
    }
    int len = p_queue_len(queue);
    for (int i = 0; i < len; i++) {
        array_set(_array, p_queue_delete_min(queue, p_queue_int_free_cb), i);
    }
    p_queue_free(queue, p_queue_int_free_cb);
}
