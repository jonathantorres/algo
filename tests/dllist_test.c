#include "unittest.h"
#include "dllist.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// utility method to print the contents of a list
// the list used in this test, will be a list of strings
void dllist_print(dllist *list)
{
    if (!list) {
        fputs("Must provide a dllist.", stderr);
        exit(EXIT_FAILURE);
    }

    printf("{");

    if (list->first != NULL) {
        dllist_node *current_node = list->first;
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
    dllist *list = dllist_new();

    assert(list != NULL, "Failed creating the list");
    assert(dllist_length(list) == 0, "List should have 0 nodes");
    assert(list->first == NULL, "First item in the list should be NULL");
    dllist_destroy(list);

    return NULL;
}

char *test_push()
{
    dllist *list = dllist_new();

    char *john = "John";
    char *luis = "Luis";
    char *chris = "Chris";
    char *mar = "Marjorie";

    dllist_push(list, john);
    dllist_push(list, luis);
    dllist_push(list, chris);
    dllist_push(list, mar);

    assert(list->first->value == john, "John must be the first node in the list");
    assert(dllist_length(list) == 4, "Length of the list must be 4");
    dllist_destroy(list);

    return NULL;
}

char *test_destroy()
{
    dllist *list = dllist_new();

    dllist_push(list, "one");
    dllist_push(list, "two");
    dllist_push(list, "three");
    dllist_destroy(list);

    return NULL;
}

char *test_clear()
{
    dllist *list = dllist_new();

    dllist_push(list, "one");
    dllist_push(list, "two");
    dllist_push(list, "three");
    dllist_clear(list);
    assert(dllist_length(list) == 0, "List length must be 0");
    dllist_destroy(list);

    return NULL;
}

char *test_shift()
{
    dllist *list = dllist_new();

    dllist_push(list, "one");
    dllist_push(list, "two");
    dllist_push(list, "three");

    assert(dllist_length(list) == 3, "List length must be 3");
    dllist_shift(list, "zero");
    assert(dllist_length(list) == 4, "List length must be 4");
    dllist_destroy(list);

    return NULL;
}

char *test_unshift()
{
    dllist *list = dllist_new();
    char *zero = "zero";
    char *one = "one";
    char *two = "two";
    char *three = "three";

    dllist_push(list, zero);
    dllist_push(list, one);
    dllist_push(list, two);
    dllist_push(list, three);

    assert(dllist_length(list) == 4, "List length must be 4");
    char *value = (char*) dllist_unshift(list);
    assert(dllist_length(list) == 3, "List length must be 3");
    assert(strcmp(zero, value) == 0, "List should be equal");
    dllist_destroy(list);

    return NULL;
}

char *test_pop()
{
    dllist *list = dllist_new();
    char *zero = "zero";
    char *one = "one";
    char *two = "two";
    char *three = "three";

    dllist_push(list, zero);
    dllist_push(list, one);
    dllist_push(list, two);
    dllist_push(list, three);

    assert(dllist_length(list) == 4, "List length must be 4");
    char *value = (char*) dllist_pop(list);
    assert(dllist_length(list) == 3, "List length must be 3");
    assert(strcmp(three, value) == 0, "List should be equal");
    dllist_destroy(list);

    return NULL;
}

char *test_remove()
{
    dllist *list = dllist_new();
    dllist_push(list, "zero");
    dllist_push(list, "one");
    dllist_push(list, "two");
    dllist_push(list, "three");

    assert(dllist_length(list) == 4, "List length must be 4");
    dllist_remove(list, "zero", cmp_func);
    assert(dllist_length(list) == 3, "List length must be 3");
    dllist_remove(list, "two", cmp_func);
    assert(dllist_length(list) == 2, "List length must be 2");
    dllist_remove(list, "one", cmp_func);
    assert(dllist_length(list) == 1, "List length must be 1");
    dllist_destroy(list);

    return NULL;
}

char *test_exists()
{
    dllist *list = dllist_new();
    dllist_push(list, "zero");
    dllist_push(list, "one");
    dllist_push(list, "two");
    dllist_push(list, "three");

    assert(dllist_length(list) == 4, "List length must be 4");
    assert(dllist_exists(list, "zero", cmp_func) == true, "zero should exist in the list");
    assert(dllist_exists(list, "one", cmp_func) == true, "one should exist in the list");
    assert(dllist_exists(list, "two", cmp_func) == true, "two should exist in the list");
    assert(dllist_exists(list, "three", cmp_func) == true, "three should exist in the list");
    assert(dllist_exists(list, "foo", cmp_func) == false, "foo shouldn't exist in the list");
    assert(dllist_length(list) == 4, "List length must be 4");
    dllist_destroy(list);

    return NULL;
}

char *test_length()
{
    dllist *list = dllist_new();
    dllist_push(list, "zero");
    dllist_push(list, "one");
    dllist_push(list, "two");
    dllist_push(list, "three");
    assert(dllist_length(list) == 4, "List length must be 4");
    dllist_destroy(list);

    return NULL;
}

int main()
{
    start_tests("doubly linked list tests");
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
    end_tests();

    return 0;
}
