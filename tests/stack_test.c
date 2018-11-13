#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unittest.h"
#include "dllist.h"
#include "stack.h"

void stack_print(stack *_stack)
{
    if (!_stack) {
        fputs("Must provide a stack.", stderr);
        exit(EXIT_FAILURE);
    }

    printf("{");

    if (_stack->first != NULL) {
        dllist_node *current_node = _stack->first;
        printf("%s,", (char*)current_node->value);

        while (current_node->next != NULL) {
            current_node = current_node->next;
            printf("%s,", (char*)current_node->value);
        }
    }

    printf("}\n");
}

char *test_new()
{
    stack *_stack = stack_new();

    assert(_stack != NULL, "Failed creating the stack");
    assert(_stack->length == 0, "The stack should have 0 nodes");

    stack_destroy(_stack);

    return NULL;
}

char *test_push()
{
    stack *_stack = stack_new();

    char *john = "John";
    char *luis = "Luis";
    char *chris = "Chris";
    char *mar = "Marjorie";

    stack_push(_stack, john);
    stack_push(_stack, luis);
    stack_push(_stack, chris);
    stack_push(_stack, mar);

    assert(stack_peek(_stack) == mar, "Marjorie must be the top item in the stack");
    assert(_stack->length == 4, "Length of the stack must be 4");

    stack_destroy(_stack);

    return NULL;
}

char *test_destroy()
{
    stack *_stack = stack_new();

    stack_push(_stack, "one");
    stack_push(_stack, "two");
    stack_push(_stack, "three");
    stack_destroy(_stack);

    return NULL;
}

char *test_clear()
{
    stack *_stack = stack_new();

    stack_push(_stack, "one");
    stack_push(_stack, "two");
    stack_push(_stack, "three");
    stack_clear(_stack);

    assert(_stack->length == 0, "Stack length must be 0");

    stack_destroy(_stack);

    return NULL;
}

char *test_pop()
{
    stack *_stack = stack_new();
    char *zero = "zero";
    char *one = "one";
    char *two = "two";
    char *three = "three";

    stack_push(_stack, zero);
    stack_push(_stack, one);
    stack_push(_stack, two);
    stack_push(_stack, three);

    assert(_stack->length == 4, "Stack length must be 4");
    char *value = (char*) stack_pop(_stack);
    assert(_stack->length == 3, "Stack length must be 3");
    assert(strcmp(three, value) == 0, "Stack value should be equal");

    stack_destroy(_stack);

    return NULL;
}

char *test_peek()
{
    stack *_stack = stack_new();

    char *john = "John";
    char *luis = "Luis";
    char *chris = "Chris";
    char *mar = "Marjorie";

    stack_push(_stack, john);
    stack_push(_stack, luis);
    stack_push(_stack, chris);
    stack_push(_stack, mar);

    assert(stack_peek(_stack) == mar, "Marjorie must be the top item in the stack");
    stack_destroy(_stack);

    return NULL;
}

int main()
{
    start_tests("stack tests");
    run_test(test_new);
    run_test(test_destroy);
    run_test(test_clear);
    run_test(test_push);
    run_test(test_pop);
    run_test(test_peek);
    end_tests();

    return 0;
}
