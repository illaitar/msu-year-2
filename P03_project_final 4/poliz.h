#include <stddef.h>
#include "stack.h"


typedef struct variable_l{
    struct variable_l *next;
    double value;
    char name[7];
} variable_l;

typedef variable_l *variables;

void add_list(variable_l **root, char what[7], double value);

void free_list(variable_l *root);

variables vars;

typedef struct{
	size_t size;
	void *data;
} Polis;

typedef char Size_elem;

typedef int (*Calculate_elem)(const void *elem, Size_elem size, Stack *stack);

int blank(Polis *polis);

int add(Polis *polis, const void *elem, Size_elem size);

void clear(Polis *polis);

int calculate_polis(const Polis *, void* , size_t size_res);
