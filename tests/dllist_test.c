#include "unittest.h"
#include "dllist.h"
#include <stdio.h>
#include <string.h>

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

char *test_create()
{
    dllist *list = dllist_new();

    assert(list != NULL, "Failed creating the list");
    assert(list->length == 0, "List should have 0 nodes");
    assert(list->first == NULL, "First item in the list should be NULL");

    dllist_destroy(list);

    return NULL;
}

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

int main()
{
    start_tests("doubly linked list tests");
    run_test(test_create);
    // run_test(test_destroy);
    // run_test(test_clear);
    end_tests();

    return 0;
}
