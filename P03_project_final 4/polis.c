#include "poliz.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


 void add_list(variable_l **root, char what[7], double value){
    if (*root == NULL){
        *root = malloc(sizeof(variable_l));
        (*root) -> value = value;
        (*root) -> next = NULL;
        strcpy((*root) -> name,what);
        return;
    }
    variable_l *kor = *root;
    while ((*root) -> next != NULL){
        if (strcmp((*root) -> name, what)==0){
            (*root) -> value = value;
        }
        (*root) = (*root)->next;
    }
    if (strcmp((*root) -> name, what)==0){
        (*root) -> value = value;
    }
    variable_l *p = malloc(sizeof(variable_l));
    strcpy(p-> name,what);
    p->value = value;
    p->next = NULL;
    (*root)->next = p;
    *root = kor;
}

void free_list(variable_l *root){
    if (root->next == NULL){
        free(root);
        
    } else {
        free_list(root->next);
        free(root);
    }
}

typedef variable_l *variables;

variables vars;

#define SAFE(call) 	do { \
	                    flag = call; \
                        if (flag != 0) { \
						    goto FINALLY; \
				        } \
				    } \
				    while (0)

int blank(Polis *polis){
    polis->size = 0;
    polis->data = NULL;
    return 0;
}

int add(Polis *polis, const void *elem, Size_elem size){
    size_t adding = size;
    size_t prev = polis->size;
    polis->size += adding;
    if (polis->data == NULL){
        polis->data = malloc(size);
    } else {
        char *p2 = realloc(polis->data,sizeof(char)*(polis->size));
        if (p2 == NULL){
            return 1;
        }
        polis->data = p2;
    }
    for(size_t i = 0; i < size; ++i){
        ((char*)polis->data)[i + prev] = ((char*)elem)[i];
    }

    return 0;
}

void clear(Polis *polis){
    free(polis->data);
    polis->size = 0;
}


int
calculate_polis(const Polis *pol, void *resp, size_t size_res)
{
	Stack stack;
	int flag = stack_init(&stack);
	if (flag != 0) {
		return flag;
	}

	for (size_t curr_size = 0; curr_size < pol->size; curr_size += sizeof (Size_elem) + ((char *)pol->data)[curr_size] ) {

		void *elem = &((char *)pol->data)[curr_size + sizeof (Size_elem)];

		Calculate_elem func;
		memcpy(&func, elem, sizeof(Calculate_elem));
		SAFE(func(elem, ((char *)pol->data)[curr_size], &stack));
	}


	SAFE(stack_pop(&stack, resp, size_res));
	
	stack_finalize(&stack);
	return 0;

FINALLY:
	stack_finalize(&stack);
	return flag;

}
