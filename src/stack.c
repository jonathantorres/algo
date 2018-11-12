#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "dllist.h"

stack *stack_new()
{
    return dllist_new();
}

void stack_push(stack *_stack, void *value)
{
    if (!_stack) {
        fputs("Must provide a valid stack.", stderr);
        return;
    }

    dllist_shift(_stack, value);
}

void *stack_pop(stack *_stack)
{
    if (!_stack) {
        fputs("Must provide a valid stack.", stderr);
        return NULL;
    }

    return dllist_unshift(_stack);
}

void *stack_peek(stack *_stack)
{
    if (!_stack) {
        fputs("Must provide a valid stack.", stderr);
        return NULL;
    }

    if (_stack->first == NULL) {
        fputs("The stack is empty", stderr);
        return NULL;
    }

    return _stack->first->value;
}

void stack_destroy(stack *_stack)
{
    if (!_stack) {
        fputs("Must provide a valid stack.", stderr);
        return;
    }

    dllist_destroy(_stack);
}

void stack_clear(stack *_stack)
{
    if (!_stack) {
        fputs("Must provide a valid stack.", stderr);
        return;
    }

    dllist_clear(_stack);
}
