#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unittest.h"
#include "stack.h"

void stack_print(stack *_stack)
{
    if (!_stack) {
        fputs("Must provide a stack.", stderr);
        exit(EXIT_FAILURE);
    }

    printf("{");
    STACK_FOREACH(_stack) {
        printf("%s,", (char*)cur->value);
    }
    printf("}\n");
}

char *test_new()
{
    stack *_stack = stack_new();

    assert(_stack != NULL, "Failed creating the stack");
    assert(stack_len(_stack) == 0, "The stack should have 0 nodes");
    stack_free(_stack);

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
    assert(stack_len(_stack) == 4, "len of the stack must be 4");
    stack_free(_stack);

    return NULL;
}

char *test_destroy()
{
    stack *_stack = stack_new();

    stack_push(_stack, "one");
    stack_push(_stack, "two");
    stack_push(_stack, "three");
    stack_free(_stack);

    return NULL;
}

char *test_clear()
{
    stack *_stack = stack_new();

    stack_push(_stack, "one");
    stack_push(_stack, "two");
    stack_push(_stack, "three");
    stack_clear(_stack);
    assert(stack_len(_stack) == 0, "Stack len must be 0");
    stack_free(_stack);

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

    assert(stack_len(_stack) == 4, "Stack len must be 4");
    char *value = (char*) stack_pop(_stack);
    assert(stack_len(_stack) == 3, "Stack len must be 3");
    assert(strcmp(three, value) == 0, "Stack value should be equal");
    stack_free(_stack);

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
    stack_free(_stack);

    return NULL;
}

char *test_len()
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
    assert(stack_len(_stack) == 4, "len of the stack should be 4");
    stack_free(_stack);

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
    run_test(test_len);
    end_tests();

    return 0;
}
