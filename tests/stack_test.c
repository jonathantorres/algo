#include "unittest.h"
#include "stack.h"
#include <stdio.h>
#include <string.h>

char *test_create()
{
    stack_create();
    // dllist *list = dllist_new();

    // assert(list != NULL, "Failed creating the list");
    // assert(list->length == 0, "List should have 0 nodes");
    // assert(list->first == NULL, "First item in the list should be NULL");

    // dllist_destroy(list);

    return NULL;
}

// char *test_push()
// {
//     dllist *list = dllist_new();

//     char *john = "John";
//     char *luis = "Luis";
//     char *chris = "Chris";
//     char *mar = "Marjorie";

//     dllist_push(list, john);
//     dllist_push(list, luis);
//     dllist_push(list, chris);
//     dllist_push(list, mar);

//     assert(list->first->value == john, "John must be the first node in the list");
//     assert(list->length == 4, "Length of the list must be 4");

//     dllist_destroy(list);
//     return NULL;
// }

// char *test_destroy()
// {
//     dllist *list = dllist_new();

//     dllist_push(list, "one");
//     dllist_push(list, "two");
//     dllist_push(list, "three");
//     dllist_destroy(list);

//     return NULL;
// }

// char *test_clear()
// {
//     dllist *list = dllist_new();

//     dllist_push(list, "one");
//     dllist_push(list, "two");
//     dllist_push(list, "three");
//     dllist_clear(list);

//     assert(list->length == 0, "List length must be 0");

//     dllist_destroy(list);

//     return NULL;
// }

// char *test_pop()
// {
//     dllist *list = dllist_new();
//     char *zero = "zero";
//     char *one = "one";
//     char *two = "two";
//     char *three = "three";

//     dllist_push(list, zero);
//     dllist_push(list, one);
//     dllist_push(list, two);
//     dllist_push(list, three);

//     assert(list->length == 4, "List length must be 4");
//     char *value = (char*) dllist_pop(list);
//     assert(list->length == 3, "List length must be 3");
//     assert(strcmp(three, value) == 0, "List should be equal");

//     dllist_destroy(list);

//     return NULL;
// }

int main()
{
    start_tests("stack tests");
    run_test(test_create);
    // run_test(test_destroy);
    // run_test(test_clear);
    // run_test(test_push);
    // run_test(test_pop);
    // run_test(test_peek);
    end_tests();

    return 0;
}
