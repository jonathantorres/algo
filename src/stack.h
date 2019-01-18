#ifndef _stack_h
#define _stack_h

#include "dllist.h"

typedef dllist stack;

stack *stack_new();
void stack_destroy(stack *_stack);
void stack_clear(stack *_stack);
void stack_push(stack *_stack, void *value);
void *stack_pop(stack *_stack);
void *stack_peek(stack *_stack);
int stack_length(stack *_stack);
#endif
