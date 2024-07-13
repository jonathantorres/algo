#include "sl_list.h"
#include "unittest.h"
#include <stdio.h>
#include <string.h>

// utility method to print the contents of a list
// the list used in this test, will be a list of strings
void sl_list_print(sl_list *list)
{
    if (!list) {
        fputs("Must provide a sl_list.", stderr);
        exit(EXIT_FAILURE);
    }

    printf("{");
    SL_LIST_FOREACH (list) {
        printf("%s,", (char *)cur->value);
    }
    printf("}\n");
}

int cmp_func(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

void sl_list_free_func(void *value)
{
    if (value) {
        free(value);
    }
}

char *test_create()
{
    sl_list *list = sl_list_new();

    assert(list != NULL, "Failed creating the list");
    assert(sl_list_len(list) == 0, "List should have 0 nodes");
    assert(list->first == NULL, "First item in the list should be NULL");

    sl_list_free(list, NULL);

    return NULL;
}

char *test_push()
{
    sl_list *list = sl_list_new();

    char *john  = "John";
    char *luis  = "Luis";
    char *chris = "Chris";
    char *mar   = "Marjorie";

    sl_list_push(list, john);
    sl_list_push(list, luis);
    sl_list_push(list, chris);
    sl_list_push(list, mar);

    assert(list->first->value == john, "John must be the first node in the list");
    assert(sl_list_len(list) == 4, "len of the list must be 4");

    sl_list_free(list, NULL);
    return NULL;
}

char *test_destroy()
{
    sl_list *list = sl_list_new();
    sl_list_push(list, "one");
    sl_list_push(list, "two");
    sl_list_push(list, "three");
    sl_list_free(list, NULL);
    return NULL;
}

char *test_clear()
{
    sl_list *list = sl_list_new();
    sl_list_push(list, "one");
    sl_list_push(list, "two");
    sl_list_push(list, "three");
    sl_list_clear(list, NULL);

    assert(sl_list_len(list) == 0, "List len must be 0");
    sl_list_free(list, NULL);

    return NULL;
}

char *test_shift()
{
    sl_list *list = sl_list_new();
    sl_list_push(list, "one");
    sl_list_push(list, "two");
    sl_list_push(list, "three");

    assert(sl_list_len(list) == 3, "List len must be 3");
    sl_list_shift(list, "zero");
    assert(sl_list_len(list) == 4, "List len must be 4");

    sl_list_free(list, NULL);

    return NULL;
}

char *test_unshift()
{
    sl_list *list = sl_list_new();
    char *zero    = "zero";
    char *one     = "one";
    char *two     = "two";
    char *three   = "three";

    sl_list_push(list, zero);
    sl_list_push(list, one);
    sl_list_push(list, two);
    sl_list_push(list, three);

    assert(sl_list_len(list) == 4, "List len must be 4");
    char *value = (char *)sl_list_unshift(list);
    assert(sl_list_len(list) == 3, "List len must be 3");
    assert(strcmp(zero, value) == 0, "List should be equal");

    sl_list_free(list, NULL);

    return NULL;
}

char *test_pop()
{
    sl_list *list = sl_list_new();
    char *zero    = "zero";
    char *one     = "one";
    char *two     = "two";
    char *three   = "three";

    sl_list_push(list, zero);
    sl_list_push(list, one);
    sl_list_push(list, two);
    sl_list_push(list, three);

    assert(sl_list_len(list) == 4, "List len must be 4");
    char *value = (char *)sl_list_pop(list);
    assert(sl_list_len(list) == 3, "List len must be 3");
    assert(strcmp(three, value) == 0, "List should be equal");

    sl_list_free(list, NULL);

    return NULL;
}

char *test_remove()
{
    sl_list *list = sl_list_new();
    sl_list_push(list, "zero");
    sl_list_push(list, "one");
    sl_list_push(list, "two");
    sl_list_push(list, "three");

    assert(sl_list_len(list) == 4, "List len must be 4");
    sl_list_remove(list, "zero", cmp_func, NULL);
    assert(sl_list_len(list) == 3, "List len must be 3");
    sl_list_remove(list, "two", cmp_func, NULL);
    assert(sl_list_len(list) == 2, "List len must be 2");
    sl_list_remove(list, "one", cmp_func, NULL);
    assert(sl_list_len(list) == 1, "List len must be 1");
    sl_list_free(list, NULL);

    return NULL;
}

char *test_exists()
{
    sl_list *list = sl_list_new();
    sl_list_push(list, "zero");
    sl_list_push(list, "one");
    sl_list_push(list, "two");
    sl_list_push(list, "three");

    assert(sl_list_len(list) == 4, "List len must be 4");
    assert(sl_list_exists(list, "zero", cmp_func) == true, "zero should exist in the list");
    assert(sl_list_exists(list, "one", cmp_func) == true, "one should exist in the list");
    assert(sl_list_exists(list, "two", cmp_func) == true, "two should exist in the list");
    assert(sl_list_exists(list, "three", cmp_func) == true, "three should exist in the list");
    assert(sl_list_exists(list, "foo", cmp_func) == false, "foo shouldn't exist in the list");
    assert(sl_list_len(list) == 4, "List len must be 4");
    sl_list_free(list, NULL);

    return NULL;
}

char *test_len()
{
    sl_list *list = sl_list_new();
    sl_list_push(list, "zero");
    sl_list_push(list, "one");
    sl_list_push(list, "two");
    sl_list_push(list, "three");
    assert(sl_list_len(list) == 4, "List len must be 4");
    sl_list_free(list, NULL);

    return NULL;
}

char *test_heap_alloc_items()
{
    char *z    = "zero";
    char *o    = "one";
    char *t    = "two";
    char *zero = malloc(strlen(z));
    char *one  = malloc(strlen(o));
    char *two  = malloc(strlen(t));

    assert(zero != NULL, "Not enough memory to allocate the zero string");
    assert(one != NULL, "Not enough memory to allocate the one string");
    assert(two != NULL, "Not enough memory to allocate the two string");

    sl_list *list = sl_list_new();
    sl_list_push(list, zero);
    sl_list_push(list, one);
    sl_list_push(list, two);
    sl_list_free(list, sl_list_free_func);

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
    run_test(test_len);
    run_test(test_heap_alloc_items);
    end_tests();

    return 0;
}
