#include "unittest.h"
#include "sllist.h"
#include <stdio.h>
#include <string.h>

// utility method to print the contents of a list
// the list used in this test, will be a list of strings
void sllist_print(sllist *list)
{
    if (!list) {
        fputs("Must provide a sllist.", stderr);
        exit(EXIT_FAILURE);
    }

    printf("{");

    if (list->first != NULL) {
        sllist_node *current_node = list->first;
        printf("%s,", (char*)current_node->value);

        while (current_node->next != NULL) {
            current_node = current_node->next;
            printf("%s,", (char*)current_node->value);
        }
    }

    printf("}\n");
}

int cmp_func(void *a, void *b)
{
    return strcmp((char*) a, (char*) b);
}

char *test_create()
{
    sllist *list = sllist_new();

    assert(list != NULL, "Failed creating the list");
    assert(sllist_length(list) == 0, "List should have 0 nodes");
    assert(list->first == NULL, "First item in the list should be NULL");

    sllist_destroy(list);

    return NULL;
}

char *test_push()
{
    sllist *list = sllist_new();

    char *john = "John";
    char *luis = "Luis";
    char *chris = "Chris";
    char *mar = "Marjorie";

    sllist_push(list, john);
    sllist_push(list, luis);
    sllist_push(list, chris);
    sllist_push(list, mar);

    assert(list->first->value == john, "John must be the first node in the list");
    assert(sllist_length(list) == 4, "Length of the list must be 4");

    sllist_destroy(list);
    return NULL;
}

char *test_destroy()
{
    sllist *list = sllist_new();
    sllist_push(list, "one");
    sllist_push(list, "two");
    sllist_push(list, "three");
    sllist_destroy(list);
    return NULL;
}

char *test_clear()
{
    sllist *list = sllist_new();
    sllist_push(list, "one");
    sllist_push(list, "two");
    sllist_push(list, "three");
    sllist_clear(list);

    assert(sllist_length(list) == 0, "List length must be 0");
    sllist_destroy(list);

    return NULL;
}

char *test_shift()
{
    sllist *list = sllist_new();
    sllist_push(list, "one");
    sllist_push(list, "two");
    sllist_push(list, "three");

    assert(sllist_length(list) == 3, "List length must be 3");
    sllist_shift(list, "zero");
    assert(sllist_length(list) == 4, "List length must be 4");

    sllist_destroy(list);

    return NULL;
}

char *test_unshift()
{
    sllist *list = sllist_new();
    char *zero = "zero";
    char *one = "one";
    char *two = "two";
    char *three = "three";

    sllist_push(list, zero);
    sllist_push(list, one);
    sllist_push(list, two);
    sllist_push(list, three);

    assert(sllist_length(list) == 4, "List length must be 4");
    char *value = (char*) sllist_unshift(list);
    assert(sllist_length(list) == 3, "List length must be 3");
    assert(strcmp(zero, value) == 0, "List should be equal");

    sllist_destroy(list);

    return NULL;
}

char *test_pop()
{
    sllist *list = sllist_new();
    char *zero = "zero";
    char *one = "one";
    char *two = "two";
    char *three = "three";

    sllist_push(list, zero);
    sllist_push(list, one);
    sllist_push(list, two);
    sllist_push(list, three);

    assert(sllist_length(list) == 4, "List length must be 4");
    char *value = (char*) sllist_pop(list);
    assert(sllist_length(list) == 3, "List length must be 3");
    assert(strcmp(three, value) == 0, "List should be equal");

    sllist_destroy(list);

    return NULL;
}

char *test_remove()
{
    sllist *list = sllist_new();
    sllist_push(list, "zero");
    sllist_push(list, "one");
    sllist_push(list, "two");
    sllist_push(list, "three");

    assert(sllist_length(list) == 4, "List length must be 4");
    sllist_remove(list, "zero", cmp_func);
    assert(sllist_length(list) == 3, "List length must be 3");
    sllist_remove(list, "two", cmp_func);
    assert(sllist_length(list) == 2, "List length must be 2");
    sllist_remove(list, "one", cmp_func);
    assert(sllist_length(list) == 1, "List length must be 1");
    sllist_destroy(list);

    return NULL;
}

char *test_exists()
{
    sllist *list = sllist_new();
    sllist_push(list, "zero");
    sllist_push(list, "one");
    sllist_push(list, "two");
    sllist_push(list, "three");

    assert(sllist_length(list) == 4, "List length must be 4");
    assert(sllist_exists(list, "zero", cmp_func) == true, "zero should exist in the list");
    assert(sllist_exists(list, "one", cmp_func) == true, "one should exist in the list");
    assert(sllist_exists(list, "two", cmp_func) == true, "two should exist in the list");
    assert(sllist_exists(list, "three", cmp_func) == true, "three should exist in the list");
    assert(sllist_exists(list, "foo", cmp_func) == false, "foo shouldn't exist in the list");
    assert(sllist_length(list) == 4, "List length must be 4");
    sllist_destroy(list);

    return NULL;
}

char *test_length()
{
    sllist *list = sllist_new();
    sllist_push(list, "zero");
    sllist_push(list, "one");
    sllist_push(list, "two");
    sllist_push(list, "three");
    assert(sllist_length(list) == 4, "List length must be 4");
    sllist_destroy(list);

    return NULL;
}

char *test_heap_alloc_items()
{
    sllist *list = sllist_new();
    char *zero = strdup("zero");
    char *one = strdup("one");
    char *two = strdup("two");
    sllist_push(list, zero);
    sllist_push(list, one);
    sllist_push(list, two);
    sllist_destroy(list);

    free(zero);
    free(one);
    free(two);

    return NULL;
}

int main()
{
    start_tests("singly linked list tests");
    run_test(test_create);
    run_test(test_push);
    run_test(test_destroy);
    run_test(test_clear);
    run_test(test_shift);
    run_test(test_unshift);
    run_test(test_pop);
    run_test(test_remove);
    run_test(test_exists);
    run_test(test_length);
    run_test(test_heap_alloc_items);
    end_tests();

    return 0;
}
