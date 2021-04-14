#ifndef POLIS
#define POLIS
#include <stddef.h>
#include "stack.h"
#include "skips.h"

typedef struct{
	size_t size;
	void *data;
} Polis;

typedef char Size_elem;

typedef int (*Calculate_elem)(const void *elem, Size_elem size, Stack *stack, Global *params);

int blank(Polis *polis);

int add(Polis *polis, const void *elem, Size_elem size);

void clear(Polis *polis);

int calculate_polis(const Polis *pol, void *resp, size_t size_res, Skips s, Stack *why);

int free_everyone(const Polis *pol, void *resp, size_t size_res, Skips s);
#endif
