#include "skips.h"

 void add_list(Skip **root, int bal){
    if (*root == NULL){
        *root = malloc(sizeof(Skip));
        (*root) -> value = 0;
        (*root) -> flag = 0;  
        (*root) -> cur_bal = bal;  
        (*root) -> next = NULL;
        return;
    }
    Skip *kor = *root;
    while ((*root) -> next != NULL){
        (*root) = (*root)->next;
    }
    Skip *p = malloc(sizeof(Skip));
    p->value = 0;
    p->flag = 0;  
    p-> cur_bal = bal;  
    p->next = NULL;
    (*root)->next = p;
    *root = kor;
}

void free_list(Skip *root){
    if (root == NULL)
        return;
    if (root->next == NULL){
        free(root);
    } else {
        free_list(root->next);
        free(root);
    }
}

void print_list(Skips root){
    printf("\n");
    while (root != NULL){
        printf("%d\n",root -> value);
        root = root -> next;
    }
}

void add_one(Skip **root){
    Skip *kor = *root;
    while ((*root) != NULL){
        if ((*root)->flag == 0){
            (*root)->value += 1;
        }
        (*root) = (*root)->next;
    }
    *root = kor;
}

void toggle_off(Skip **root, int bal){
    if (root == NULL){
        return;
    }
    Skip *kor = *root;
    while ((*root) != NULL){
        if ((*root)->flag == 0){
            if ((*root)->cur_bal >= bal){
                (*root)->flag = 1;
            }
        }
        (*root) = (*root)->next;
    }
    *root = kor;
}



