#include "unittest.h"
#include "cllist.h"
#include <stdio.h>
#include <string.h>

// utility method to print the contents of a list
// the list used in this test, will be a list of strings
void cllist_print(cllist *list)
{
    if (!list) {
        fputs("Must provide a cllist.", stderr);
        exit(EXIT_FAILURE);
    }

    printf("{");

    if (list->first != NULL) {
        cllist_node *current_node = list->first;
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
    cllist *list = cllist_new();

    assert(list != NULL, "Failed creating the list");
    assert(list->length == 0, "List should have 0 nodes");
    assert(list->first == NULL, "First item in the list should be NULL");

    cllist_destroy(list);

    return NULL;
}

char *test_push()
{
    cllist *list = cllist_new();

    char *john = "John";
    char *luis = "Luis";
    char *chris = "Chris";
    char *mar = "Marjorie";

    cllist_push(list, john);
    cllist_push(list, luis);
    cllist_push(list, chris);
    cllist_push(list, mar);

    assert(list->first->value == john, "John must be the first node in the list");
    assert(list->length == 4, "Length of the list must be 4");

    cllist_destroy(list);
    return NULL;
}

char *test_destroy()
{
    cllist *list = cllist_new();

    cllist_push(list, "one");
    cllist_push(list, "two");
    cllist_push(list, "three");
    cllist_destroy(list);

    return NULL;
}

char *test_clear()
{
    cllist *list = cllist_new();

    cllist_push(list, "one");
    cllist_push(list, "two");
    cllist_push(list, "three");
    cllist_clear(list);

    assert(list->length == 0, "List length must be 0");

    cllist_destroy(list);

    return NULL;
}

char *test_shift()
{
    cllist *list = cllist_new();

    cllist_push(list, "one");
    cllist_push(list, "two");
    cllist_push(list, "three");

    assert(list->length == 3, "List length must be 3");
    cllist_shift(list, "zero");
    assert(list->length == 4, "List length must be 4");

    cllist_destroy(list);

    return NULL;
}

char *test_unshift()
{
    cllist *list = cllist_new();
    char *zero = "zero";
    char *one = "one";
    char *two = "two";
    char *three = "three";

    cllist_push(list, zero);
    cllist_push(list, one);
    cllist_push(list, two);
    cllist_push(list, three);

    assert(list->length == 4, "List length must be 4");
    char *value = (char*) cllist_unshift(list);
    assert(list->length == 3, "List length must be 3");
    assert(strcmp(zero, value) == 0, "List should be equal");

    cllist_destroy(list);

    return NULL;
}

char *test_pop()
{
    cllist *list = cllist_new();
    char *zero = "zero";
    char *one = "one";
    char *two = "two";
    char *three = "three";

    cllist_push(list, zero);
    cllist_push(list, one);
    cllist_push(list, two);
    cllist_push(list, three);

    assert(list->length == 4, "List length must be 4");
    char *value = (char*) cllist_pop(list);
    assert(list->length == 3, "List length must be 3");
    assert(strcmp(three, value) == 0, "List should be equal");

    cllist_destroy(list);

    return NULL;
}

char *test_remove()
{
    cllist *list = cllist_new();
    cllist_push(list, "zero");
    cllist_push(list, "one");
    cllist_push(list, "two");
    cllist_push(list, "three");

    assert(list->length == 4, "List length must be 4");
    cllist_remove(list, "zero", cmp_func);
    assert(list->length == 3, "List length must be 3");
    cllist_remove(list, "two", cmp_func);
    assert(list->length == 2, "List length must be 2");
    cllist_remove(list, "one", cmp_func);
    assert(list->length == 1, "List length must be 1");

    cllist_destroy(list);

    return NULL;
}

char *test_exists()
{
    cllist *list = cllist_new();
    cllist_push(list, "zero");
    cllist_push(list, "one");
    cllist_push(list, "two");
    cllist_push(list, "three");

    assert(list->length == 4, "List length must be 4");
    assert(cllist_exists(list, "zero", cmp_func) == 1, "zero should exist in the list");
    assert(cllist_exists(list, "one", cmp_func) == 1, "one should exist in the list");
    assert(cllist_exists(list, "two", cmp_func) == 1, "two should exist in the list");
    assert(cllist_exists(list, "three", cmp_func) == 1, "three should exist in the list");
    assert(cllist_exists(list, "foo", cmp_func) == 0, "foo shouldn't exist in the list");
    assert(list->length == 4, "List length must be 4");

    cllist_destroy(list);

    return NULL;
}

int main()
{
    start_tests("circular linked list tests");
    run_test(test_create);
    // run_test(test_push);
    // run_test(test_destroy);
    // run_test(test_clear);
    // run_test(test_shift);
    // run_test(test_unshift);
    // run_test(test_pop);
    // run_test(test_remove);
    // run_test(test_exists);
    end_tests();

    return 0;
}
