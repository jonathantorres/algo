#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "unittest.h"
#include "p_queue.h"

int p_queue_int_traverse_count = 0;

int p_queue_int_cmp(void *a, void *b)
{
    if (*(int*)a < *(int*)b) {
        return -1;
    } else if (*(int*)a > *(int*)b) {
        return 1;
    } else {
        return 0;
    }
}

void p_queue_int_free_cb(void *value)
{
    if (value) {
        // nothing to free here
    }
}

void p_queue_int_traverse_cb(void *value)
{
    if (value) {
        p_queue_int_traverse_count++;
    }
    // printf("value: %d\n", *(int *)value);
}

char *test_new()
{
    p_queue *queue = p_queue_new(p_queue_int_cmp);
    assert(queue != NULL, "p_queue cannot be NULL");
    p_queue_free(queue, p_queue_int_free_cb);
    return NULL;
}

char *test_free()
{
    p_queue *queue = p_queue_new(p_queue_int_cmp);
    p_queue_free(queue, p_queue_int_free_cb);
    return NULL;
}

char *test_insert()
{
    int n1 = 10;
    int n2 = 4;
    int n3 = 30;
    int n4 = 28;

    p_queue *queue = p_queue_new(p_queue_int_cmp);
    p_queue_insert(queue, &n1);
    p_queue_insert(queue, &n2);
    p_queue_insert(queue, &n3);
    p_queue_insert(queue, &n4);
    p_queue_free(queue, p_queue_int_free_cb);
    return NULL;
}

char *test_find_min()
{
    int n1 = 10;
    int n2 = 4;
    int n3 = 30;
    int n4 = 28;

    p_queue *queue = p_queue_new(p_queue_int_cmp);
    p_queue_insert(queue, &n1);
    p_queue_insert(queue, &n2);
    p_queue_insert(queue, &n3);
    p_queue_insert(queue, &n4);

    int *min = p_queue_find_min(queue);
    assert(*min == 4, "Min should be 4");
    p_queue_free(queue, p_queue_int_free_cb);
    return NULL;
}

char *test_delete_min()
{
    int n1 = 10;
    int n2 = 4;
    int n3 = 30;
    int n4 = 28;

    p_queue *queue = p_queue_new(p_queue_int_cmp);
    p_queue_insert(queue, &n1);
    p_queue_insert(queue, &n2);
    p_queue_insert(queue, &n3);
    p_queue_insert(queue, &n4);

    assert(p_queue_len(queue) == 4, "p_queue len should be 4");
    int *min = p_queue_delete_min(queue, p_queue_int_free_cb);
    assert(*min == 4, "Min should be 4");
    assert(p_queue_len(queue) == 3, "p_queue len should be 3");
    p_queue_free(queue, p_queue_int_free_cb);
    return NULL;
}

char *test_len()
{
    int n1 = 10;
    int n2 = 4;
    int n3 = 30;
    int n4 = 28;

    p_queue *queue = p_queue_new(p_queue_int_cmp);
    p_queue_insert(queue, &n1);
    p_queue_insert(queue, &n2);
    p_queue_insert(queue, &n3);
    p_queue_insert(queue, &n4);

    assert(p_queue_len(queue) == 4, "p_queue len should be 4");
    p_queue_delete_min(queue, p_queue_int_free_cb);
    assert(p_queue_len(queue) == 3, "p_queue len should be 3");
    p_queue_delete_min(queue, p_queue_int_free_cb);
    assert(p_queue_len(queue) == 2, "p_queue len should be 2");
    return NULL;
}

char *test_traverse()
{
    int n1 = 10;
    int n2 = 4;
    int n3 = 30;
    int n4 = 28;

    p_queue *queue = p_queue_new(p_queue_int_cmp);
    p_queue_insert(queue, &n1);
    p_queue_insert(queue, &n2);
    p_queue_insert(queue, &n3);
    p_queue_insert(queue, &n4);
    p_queue_traverse(queue, p_queue_int_traverse_cb);
    assert(p_queue_int_traverse_count == 4, "Traverse count should be 4!");

    return NULL;
}

int main()
{
    start_tests("p_queue tests");
    run_test(test_new);
    run_test(test_free);
    run_test(test_insert);
    run_test(test_find_min);
    run_test(test_delete_min);
    run_test(test_len);
    run_test(test_traverse);
    end_tests();

    return 0;
}
