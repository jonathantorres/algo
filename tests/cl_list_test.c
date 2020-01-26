#include "unittest.h"
#include "cl_list.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// utility method to print the contents of a list
// the list used in this test, will be a list of strings
void cl_list_print(cl_list *list)
{
    if (!list) {
        fputs("Must provide a cl_list.", stderr);
        exit(EXIT_FAILURE);
    }

    printf("{");
    CL_LIST_FOREACH(list) {
        printf("%s,", (char*)cur->value);
    }
    printf("}\n");
}

int cmp_func(void *a, void *b)
{
    return strcmp((char*) a, (char*) b);
}

char *test_create()
{
    cl_list *list = cl_list_new();

    assert(list != NULL, "Failed creating the list");
    assert(cl_list_length(list) == 0, "List should have 0 nodes");
    assert(list->first == NULL, "First item in the list should be NULL");
    assert(list->last == NULL, "Last item in the list should be NULL");
    cl_list_free(list);

    return NULL;
}

char *test_push()
{
    cl_list *list = cl_list_new();

    char *john = "John";
    char *luis = "Luis";
    char *chris = "Chris";
    char *mar = "Marjorie";

    cl_list_push(list, john);
    cl_list_push(list, luis);
    cl_list_push(list, chris);
    cl_list_push(list, mar);

    assert(list->first->value == john, "John must be the first node in the list");
    assert(cl_list_length(list) == 4, "Length of the list must be 4");
    assert(list->last->value == mar, "Marjorie must be the last node in the list");
    cl_list_free(list);

    return NULL;
}

char *test_destroy()
{
    cl_list *list = cl_list_new();

    cl_list_push(list, "one");
    cl_list_push(list, "two");
    cl_list_push(list, "three");
    cl_list_free(list);

    return NULL;
}

char *test_clear()
{
    cl_list *list = cl_list_new();

    cl_list_push(list, "one");
    cl_list_push(list, "two");
    cl_list_push(list, "three");
    cl_list_clear(list);
    assert(cl_list_length(list) == 0, "List length must be 0");
    cl_list_free(list);

    return NULL;
}

char *test_shift()
{
    cl_list *list = cl_list_new();

    cl_list_push(list, "one");
    cl_list_push(list, "two");
    cl_list_push(list, "three");
    assert(cl_list_length(list) == 3, "List length must be 3");
    cl_list_shift(list, "zero");
    assert(cl_list_length(list) == 4, "List length must be 4");
    cl_list_free(list);

    return NULL;
}

char *test_unshift()
{
    cl_list *list = cl_list_new();
    char *zero = "zero";
    char *one = "one";
    char *two = "two";
    char *three = "three";

    cl_list_push(list, zero);
    cl_list_push(list, one);
    cl_list_push(list, two);
    cl_list_push(list, three);

    assert(cl_list_length(list) == 4, "List length must be 4");
    char *value = (char*) cl_list_unshift(list);
    assert(cl_list_length(list) == 3, "List length must be 3");
    assert(strcmp(zero, value) == 0, "List should be equal");
    cl_list_free(list);

    return NULL;
}

char *test_pop()
{
    cl_list *list = cl_list_new();
    char *zero = "zero";
    char *one = "one";
    char *two = "two";
    char *three = "three";

    cl_list_push(list, zero);
    cl_list_push(list, one);
    cl_list_push(list, two);
    cl_list_push(list, three);

    assert(cl_list_length(list) == 4, "List length must be 4");
    char *value = (char*) cl_list_pop(list);
    assert(cl_list_length(list) == 3, "List length must be 3");
    assert(strcmp(three, value) == 0, "List should be equal");
    cl_list_free(list);

    return NULL;
}

char *test_remove()
{
    cl_list *list = cl_list_new();
    cl_list_push(list, "zero");
    cl_list_push(list, "one");
    cl_list_push(list, "two");
    cl_list_push(list, "three");

    assert(cl_list_length(list) == 4, "List length must be 4");
    cl_list_remove(list, "zero", cmp_func);
    assert(cl_list_length(list) == 3, "List length must be 3");
    cl_list_remove(list, "two", cmp_func);
    assert(cl_list_length(list) == 2, "List length must be 2");
    cl_list_remove(list, "one", cmp_func);
    assert(cl_list_length(list) == 1, "List length must be 1");
    cl_list_free(list);

    return NULL;
}

char *test_exists()
{
    cl_list *list = cl_list_new();
    cl_list_push(list, "zero");
    cl_list_push(list, "one");
    cl_list_push(list, "two");
    cl_list_push(list, "three");

    assert(cl_list_length(list) == 4, "List length must be 4");
    assert(cl_list_exists(list, "zero", cmp_func) == true, "zero should exist in the list");
    assert(cl_list_exists(list, "one", cmp_func) == true, "one should exist in the list");
    assert(cl_list_exists(list, "two", cmp_func) == true, "two should exist in the list");
    assert(cl_list_exists(list, "three", cmp_func) == true, "three should exist in the list");
    assert(cl_list_exists(list, "foo", cmp_func) == false, "foo shouldn't exist in the list");
    assert(cl_list_length(list) == 4, "List length must be 4");
    cl_list_free(list);

    return NULL;
}

char *test_length()
{
    cl_list *list = cl_list_new();
    cl_list_push(list, "zero");
    cl_list_push(list, "one");
    cl_list_push(list, "two");
    cl_list_push(list, "three");
    assert(cl_list_length(list) == 4, "List length must be 4");
    cl_list_free(list);

    return NULL;
}

int main()
{
    start_tests("circular linked list tests");
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
