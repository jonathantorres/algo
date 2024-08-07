#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unittest.h"
#include "queue.h"

void queue_print(queue *_queue)
{
    if (!_queue) {
        fputs("Must provide a queue.", stderr);
        exit(EXIT_FAILURE);
    }

    printf("{");
    QUEUE_FOREACH(_queue) {
        printf("%s,", (char*)cur->value);
    }
    printf("}\n");
}

void queue_free_cb_func(void *value)
{
    if (value) {
        free(value);
    }
}

char *test_new()
{
    queue *_queue = queue_new();

    assert(_queue != NULL, "Failed creating the queue");
    assert(queue_len(_queue) == 0, "The queue should have 0 nodes");
    queue_free(_queue, NULL);

    return NULL;
}

char *test_enqueue()
{
    queue *_queue = queue_new();

    char *john = "John";
    char *luis = "Luis";
    char *chris = "Chris";
    char *mar = "Marjorie";

    queue_enqueue(_queue, john);
    queue_enqueue(_queue, luis);
    queue_enqueue(_queue, chris);
    queue_enqueue(_queue, mar);

    assert(queue_peek(_queue) == john, "John must be the top item in the queue");
    assert(queue_len(_queue) == 4, "len of the queue must be 4");
    queue_free(_queue, NULL);

    return NULL;
}

char *test_free()
{
    queue *_queue = queue_new();

    queue_enqueue(_queue, "one");
    queue_enqueue(_queue, "two");
    queue_enqueue(_queue, "three");
    queue_free(_queue, NULL);

    return NULL;
}

char *test_clear()
{
    queue *_queue = queue_new();

    queue_enqueue(_queue, "one");
    queue_enqueue(_queue, "two");
    queue_enqueue(_queue, "three");
    queue_clear(_queue, NULL);
    assert(queue_len(_queue) == 0, "queue len must be 0");
    queue_free(_queue, NULL);

    return NULL;
}

char *test_dequeue()
{
    queue *_queue = queue_new();
    char *zero = "zero";
    char *one = "one";
    char *two = "two";
    char *three = "three";

    queue_enqueue(_queue, zero);
    queue_enqueue(_queue, one);
    queue_enqueue(_queue, two);
    queue_enqueue(_queue, three);

    assert(queue_len(_queue) == 4, "queue len must be 4");
    char *value = (char*) queue_dequeue(_queue);
    assert(queue_len(_queue) == 3, "queue len must be 3");
    assert(strcmp(zero, value) == 0, "queue value should be equal");
    queue_free(_queue, NULL);

    return NULL;
}

char *test_peek()
{
    queue *_queue = queue_new();

    char *john = "John";
    char *luis = "Luis";
    char *chris = "Chris";
    char *mar = "Marjorie";

    queue_enqueue(_queue, john);
    queue_enqueue(_queue, luis);
    queue_enqueue(_queue, chris);
    queue_enqueue(_queue, mar);
    assert(queue_peek(_queue) == john, "John must be the top item in the queue");
    queue_free(_queue, NULL);

    return NULL;
}

char *test_len()
{
    queue *_queue = queue_new();

    char *john = "John";
    char *luis = "Luis";
    char *chris = "Chris";
    char *mar = "Marjorie";

    queue_enqueue(_queue, john);
    queue_enqueue(_queue, luis);
    queue_enqueue(_queue, chris);
    queue_enqueue(_queue, mar);
    assert(queue_len(_queue) == 4, "len of queue should be 4");
    queue_free(_queue, NULL);

    return NULL;
}

int main()
{
    start_tests("queue tests");
    run_test(test_new);
    run_test(test_free);
    run_test(test_clear);
    run_test(test_enqueue);
    run_test(test_dequeue);
    run_test(test_peek);
    run_test(test_len);
    end_tests();

    return 0;
}
