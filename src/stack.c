#include "stack.h"

stack *stack_new()
{
    return dl_list_new();
}

void stack_push(stack *_stack, void *value)
{
    if (!_stack) {
        fputs("Must provide a valid stack.", stderr);
        return;
    }

    dl_list_shift(_stack, value);
}

void *stack_pop(stack *_stack)
{
    if (!_stack) {
        fputs("Must provide a valid stack.", stderr);
        return NULL;
    }

    return dl_list_unshift(_stack);
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

void stack_free(stack *_stack)
{
    if (!_stack) {
        fputs("Must provide a valid stack.", stderr);
        return;
    }

    dl_list_free(_stack);
}

void stack_clear(stack *_stack)
{
    if (!_stack) {
        fputs("Must provide a valid stack.", stderr);
        return;
    }

    dl_list_clear(_stack);
}

int stack_len(stack *_stack)
{
    if (!_stack) {
        fputs("Must provide a valid stack.", stderr);
        return 0;
    }

    return dl_list_len(_stack);
}
