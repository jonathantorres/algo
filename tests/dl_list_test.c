#include "unittest.h"
#include "dl_list.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// utility method to print the contents of a list
// the list used in this test, will be a list of strings
void dl_list_print(dl_list *list)
{
    if (!list) {
        fputs("Must provide a dl_list.", stderr);
        exit(EXIT_FAILURE);
    }

    printf("{");
    DL_LIST_FOREACH(list) {
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
    dl_list *list = dl_list_new();

    assert(list != NULL, "Failed creating the list");
    assert(dl_list_len(list) == 0, "List should have 0 nodes");
    assert(list->first == NULL, "First item in the list should be NULL");
    dl_list_free(list);

    return NULL;
}

char *test_push()
{
    dl_list *list = dl_list_new();

    char *john = "John";
    char *luis = "Luis";
    char *chris = "Chris";
    char *mar = "Marjorie";

    dl_list_push(list, john);
    dl_list_push(list, luis);
    dl_list_push(list, chris);
    dl_list_push(list, mar);

    assert(list->first->value == john, "John must be the first node in the list");
    assert(dl_list_len(list) == 4, "len of the list must be 4");
    dl_list_free(list);

    return NULL;
}

char *test_destroy()
{
    dl_list *list = dl_list_new();

    dl_list_push(list, "one");
    dl_list_push(list, "two");
    dl_list_push(list, "three");
    dl_list_free(list);

    return NULL;
}

char *test_clear()
{
    dl_list *list = dl_list_new();

    dl_list_push(list, "one");
    dl_list_push(list, "two");
    dl_list_push(list, "three");
    dl_list_clear(list);
    assert(dl_list_len(list) == 0, "List len must be 0");
    dl_list_free(list);

    return NULL;
}

char *test_shift()
{
    dl_list *list = dl_list_new();

    dl_list_push(list, "one");
    dl_list_push(list, "two");
    dl_list_push(list, "three");

    assert(dl_list_len(list) == 3, "List len must be 3");
    dl_list_shift(list, "zero");
    assert(dl_list_len(list) == 4, "List len must be 4");
    dl_list_free(list);

    return NULL;
}

char *test_unshift()
{
    dl_list *list = dl_list_new();
    char *zero = "zero";
    char *one = "one";
    char *two = "two";
    char *three = "three";

    dl_list_push(list, zero);
    dl_list_push(list, one);
    dl_list_push(list, two);
    dl_list_push(list, three);

    assert(dl_list_len(list) == 4, "List len must be 4");
    char *value = (char*) dl_list_unshift(list);
    assert(dl_list_len(list) == 3, "List len must be 3");
    assert(strcmp(zero, value) == 0, "List should be equal");
    dl_list_free(list);

    return NULL;
}

char *test_pop()
{
    dl_list *list = dl_list_new();
    char *zero = "zero";
    char *one = "one";
    char *two = "two";
    char *three = "three";

    dl_list_push(list, zero);
    dl_list_push(list, one);
    dl_list_push(list, two);
    dl_list_push(list, three);

    assert(dl_list_len(list) == 4, "List len must be 4");
    char *value = (char*) dl_list_pop(list);
    assert(dl_list_len(list) == 3, "List len must be 3");
    assert(strcmp(three, value) == 0, "List should be equal");
    dl_list_free(list);

    return NULL;
}

char *test_remove()
{
    dl_list *list = dl_list_new();
    dl_list_push(list, "zero");
    dl_list_push(list, "one");
    dl_list_push(list, "two");
    dl_list_push(list, "three");

    assert(dl_list_len(list) == 4, "List len must be 4");
    dl_list_remove(list, "zero", cmp_func);
    assert(dl_list_len(list) == 3, "List len must be 3");
    dl_list_remove(list, "two", cmp_func);
    assert(dl_list_len(list) == 2, "List len must be 2");
    dl_list_remove(list, "one", cmp_func);
    assert(dl_list_len(list) == 1, "List len must be 1");
    dl_list_free(list);

    return NULL;
}

char *test_exists()
{
    dl_list *list = dl_list_new();
    dl_list_push(list, "zero");
    dl_list_push(list, "one");
    dl_list_push(list, "two");
    dl_list_push(list, "three");

    assert(dl_list_len(list) == 4, "List len must be 4");
    assert(dl_list_exists(list, "zero", cmp_func) == true, "zero should exist in the list");
    assert(dl_list_exists(list, "one", cmp_func) == true, "one should exist in the list");
    assert(dl_list_exists(list, "two", cmp_func) == true, "two should exist in the list");
    assert(dl_list_exists(list, "three", cmp_func) == true, "three should exist in the list");
    assert(dl_list_exists(list, "foo", cmp_func) == false, "foo shouldn't exist in the list");
    assert(dl_list_len(list) == 4, "List len must be 4");
    dl_list_free(list);

    return NULL;
}

char *test_len()
{
    dl_list *list = dl_list_new();
    dl_list_push(list, "zero");
    dl_list_push(list, "one");
    dl_list_push(list, "two");
    dl_list_push(list, "three");
    assert(dl_list_len(list) == 4, "List len must be 4");
    dl_list_free(list);

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
    run_test(test_len);
    end_tests();

    return 0;
}
