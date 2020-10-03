#include "stack.h"

stack *stack_new()
{
    return dl_list_new();
}

void stack_push(stack *_stack, void *value)
{
    if (!_stack) {
        return;
    }

    dl_list_shift(_stack, value);
}

void *stack_pop(stack *_stack)
{
    if (!_stack) {
        return NULL;
    }

    return dl_list_unshift(_stack);
}

void *stack_peek(stack *_stack)
{
    if (!_stack) {
        return NULL;
    }

    if (_stack->first == NULL) {
        return NULL;
    }

    return _stack->first->value;
}

void stack_free(stack *_stack, stack_free_cb cb)
{
    if (!_stack) {
        return;
    }

    dl_list_free(_stack, cb);
}

void stack_clear(stack *_stack, stack_free_cb cb)
{
    if (!_stack) {
        return;
    }

    dl_list_clear(_stack, cb);
}

int stack_len(stack *_stack)
{
    if (!_stack) {
        return 0;
    }

    return dl_list_len(_stack);
}
