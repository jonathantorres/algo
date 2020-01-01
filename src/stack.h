#ifndef _stack_h
#define _stack_h

#include <stdio.h>
#include <stdlib.h>
#include "dl_list.h"

typedef dl_list stack;

stack *stack_new();
void stack_destroy(stack *_stack);
void stack_clear(stack *_stack);
void stack_push(stack *_stack, void *value);
void *stack_pop(stack *_stack);
void *stack_peek(stack *_stack);
int stack_length(stack *_stack);

// Macro usage:
// STACK_FOREACH(stack) {
    // your code here
    // you can use the variable "cur"
    // inside of it that references the current item of the stack
// }
#define STACK_FOREACH(stack) dl_list_node *cur = NULL; \
    for (cur = (stack)->first; cur != NULL; cur = cur->next)

#endif
