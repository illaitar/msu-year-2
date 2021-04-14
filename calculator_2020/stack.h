#include <stddef.h>
#define STACK_OVERFLOW 1
#define STACK_UNDERFLOW 2

typedef struct Stack Stack;

typedef struct Stack{
    size_t size;
    size_t cap;
    char *data;
} Stack;

int stack_init(Stack* stack);

void stack_finalize(Stack *stack);

int stack_pop(Stack *stack, void *res, size_t size_res);

int stack_push(Stack *stack, void *var, size_t size_var);
