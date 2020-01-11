#include "p_queue.h"

p_queue *p_queue_new(p_queue_cmp cmp)
{
    p_queue *queue = malloc(sizeof(p_queue));
    if (!queue) {
        return NULL;
    }

    bs_tree *tree = bs_tree_new(cmp);
    if (!tree) {
        free(queue);
        return NULL;
    }
    queue->tree = tree;

    return queue;
}

void p_queue_insert(p_queue *queue, void *value)
{
    if (!queue) {
        return;
    }
    bs_tree_insert(queue->tree, value);
}

void *p_queue_find_min(p_queue *queue)
{
    if (!queue) {
        return NULL;
    }
    return bs_tree_find_min(queue->tree);
}

void *p_queue_delete_min(p_queue *queue, p_queue_cb cb)
{
    if (!queue) {
        return NULL;
    }
    void *min = bs_tree_find_min(queue->tree);
    if (!min) {
        return NULL;
    }

    bs_tree_delete(queue->tree, min, cb);

    return min;
}

int p_queue_len(p_queue *queue)
{
    if (!queue) {
        return -1;
    }
    return queue->tree->len;
}

void p_queue_traverse(p_queue *queue, p_queue_cb cb)
{
    if (!queue) {
        return;
    }
    bs_tree_traverse(queue->tree, cb);
}

void p_queue_free(p_queue *queue, p_queue_cb cb)
{
    if (!queue) {
        return;
    }
    bs_tree_free(queue->tree, cb);
    free(queue);
}
