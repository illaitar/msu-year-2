#ifndef stdio
#include <stdio.h>
#endif

#ifndef stack
#include "stack.h"
#endif

#ifndef stdlib
#include <stdlib.h>
#endif

#ifndef stddef
#include <stddef.h>
#endif

#define STACK_INIT_SIZE  1024
#define STACK_ADD  1024

int stack_init(Stack *stack){
    stack->size = 0;
    stack->cap = 0;
    stack->data = NULL;
    return 0;
}

int stack_resize(Stack *stack){
    stack->cap += STACK_ADD;
    stack->data = (char*) realloc (stack->data, stack->cap * sizeof(char));
    if (stack->data == NULL){
        return STACK_OVERFLOW;
    }
    return 0;
}

int stack_push(Stack *stack, void *var, size_t size_var){
    if (stack->size + size_var >= stack->cap){
        if (stack_resize(stack) == STACK_OVERFLOW){
            return STACK_OVERFLOW;
        }
    }
    for (size_t i = 0; i < size_var; ++i){
        stack->data[stack->size] = ((char*)var)[i];
        stack->size += 1;
    }
    return 0;
}

int stack_pop(Stack *stack, void *res, size_t size_res){
    int flag = stack->size - size_res;
    if (flag < 0){
        return STACK_UNDERFLOW;
    }
    stack->size -= size_res;
    for (size_t i = 0; i < size_res; ++i){
        ((char*)res)[i] = stack->data[stack->size + i];
    }
    return 0;
}

void stack_finalize(Stack *stack){
    free(stack->data);
    stack->size = 0;
}
