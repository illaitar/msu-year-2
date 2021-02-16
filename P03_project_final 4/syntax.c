#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "poliz.h"
#include "float.h"

int balance;
char prev = '\0';
int is_op =0;
int is_num = 0;
int bracket_l = 0;
int bracket_r = 0;

int
add_func(const void *elem, Size_elem size, Stack *stack)
{
    double op_1 = 0, op_2 = 0, res = 0;
    stack_pop(stack, &op_1, sizeof(double));
    stack_pop(stack, &op_2, sizeof(double));
    res = op_1 + op_2;
    stack_push(stack, &res, sizeof(double));
    return 0;
}

int
sub_func(const void *elem, Size_elem size, Stack *stack)
{
    double op_1 = 0, op_2 = 0, res = 0;
    stack_pop(stack, &op_1, sizeof(double));
    stack_pop(stack, &op_2, sizeof(double));
    res = op_2 - op_1;
    stack_push(stack, &res, sizeof(double));
    return 0;
}

int
multi_func(const void *elem, Size_elem size, Stack *stack)
{
    double op_1 = 0, op_2 = 0, res = 0;
    stack_pop(stack, &op_1, sizeof(double));
    stack_pop(stack, &op_2, sizeof(double));
    res = op_1 * op_2;
    stack_push(stack, &res, sizeof(double));
    return 0;
}

int
div_func(const void *elem, Size_elem size, Stack *stack)
{
    double op_1 = 0, op_2 = 0, res = 0;
    stack_pop(stack, &op_1, sizeof(double));
    stack_pop(stack, &op_2, sizeof(double));
    if (op_1 < FLT_EPSILON){
        return 14;
    }
    res = op_2 / op_1;
    stack_push(stack, &res, sizeof(double));
    return 0;
}

int
num_func(const void *elem, Size_elem size, Stack *stack)
{
    double *op = malloc(sizeof(double));
    if (op == NULL){
        return 17;
    }
    for (size_t gh = 0; gh < size - sizeof(Calculate_elem); ++gh){
       ((char*)op)[gh] = ((char*)elem)[gh + sizeof(Calculate_elem)];
    }
    stack_push(stack, op, sizeof(double));
    free(op);
    return 0;
}

int
var_func(const void *elem, Size_elem size, Stack *stack)
{
    char op[7];
    for (int z = 0; z < 7; ++z){
        op[z] = '\0';
    }
    //printf("var size = %lu", size - sizeof(Calculate_elem));
    for (size_t gh = 0; gh < size - sizeof(Calculate_elem); ++gh){
        op[gh] =  ((char*)elem)[gh + sizeof(Calculate_elem)];
    }
    //printf("var name = %s\n", op);
    variable_l *a = vars;
    if (a == NULL){
        return 1;
    }
    while ( (a != NULL) && (strcmp((a -> name),op) != 0)){
        a = a->next;
    }
    if (a == NULL){
        return 1;
    }
    double haha = a->value;
    stack_push(stack, &haha, sizeof(double));
    return 0;
}

void next1(int *otype, char** lexem){
    //clear spaces till next lexem
    char c;
    if (prev == '\0'){
        //начался ввод
        while(((c = getchar()) == ' ')&&(c != '\n')&&(c != EOF)){
           c = getchar();
        }
        if ((c == '\n') || (c == EOF)){
            //empty
            *otype = -1;
            is_op = 0;
            *lexem = NULL;
            return;
        }
    } else {
    
        c = prev;
        while((c == ' ')&&(c != '\n') && (c != EOF)){
            c = getchar();
        }
        if ((c == '\n') || (c == EOF)){
            //empty
            *otype = -1;
            is_op = 0;
            *lexem = NULL;
            return;
        }
    }

    //number
    if (((c >= '0') && (c <= '9'))|| (c == '.')){
        int dot = 0;
        if (c == '.'){
            dot = 1;
        }
        bracket_r = 0;
        bracket_l = 0;
        char *line = malloc(sizeof(char)*1024);
        if (line == NULL){
            *otype = -11;
            free(line);
            *lexem = NULL;
            return;
        }
        int cur_size = 1024;
        *otype = 0;
        is_op = 0;
        if (is_num == 1){
            *otype = -8;
            free(line);
            *lexem = NULL;
            return;
        }
        is_num = 1;
        int i = 1;
        line[0] = c;
        while( ((c = getchar()) != '\n') && (c != EOF) && (((c >= '0') && (c <= '9')) || (c == '.') )){
            if (c== '.'){
                dot++;
            }
            if (dot > 1){
                //bad number
                *otype = -3;
                free(line);
                *lexem = NULL;
                return;
            }   
            line[i] = c;
            i++;
            if (i == cur_size){
                line = realloc(line, sizeof(char)*((cur_size + 1024)));
            }
        }
        prev = c;
        if (!((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '(') || (c == ')') || (c == '\n')|| (c == ' ') || (c == EOF))){
            *otype = -3;   
            free(line); 
            *lexem = NULL;
            return;
        }
        *lexem = malloc(sizeof(char) * (i+1));
        if (*lexem == NULL){
            *otype = -11;
            free(line);
            *lexem = NULL;
            return;
        }
        for (int  z = 0; z < i; ++z){
            (*lexem)[z] = line[z];
        }
        free(line);
        (*lexem)[i] = '\0';
        return;
    }
    //variable
    if ((c >= 'a') && (c <= 'z')){
        bracket_r = 0;
        bracket_l = 0;
        char *line = malloc(sizeof(char)*1024);
        if (line == NULL){
            *otype = -11;
            free(line);
            *lexem = NULL;
            return;
        }
        int cur_size = 1024;
        *otype = 2;
        if (is_num == 1){
            *otype = -8;   
            free(line); 
            *lexem = NULL;
            return;
        }
        is_num = 1;
        is_op = 0;
        int i = 1;
        line[0] = c;
        while( ((c = getchar()) != '\n') &&  (c != EOF) && (((c >= '0') && (c <= '9')) || (c == '_') || (  ((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z'))))){ 
            line[i] = c;
            i++;
            if (i == cur_size){
                line = realloc(line, sizeof(char)*((cur_size + 1024)));
            }
        }
        prev = c;
        if (!((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '(') || (c == ')') || (c == '\n')|| (c == ' ') || (c == EOF))){
            *otype = -9;   
            free(line); 
            *lexem = NULL;
            return;
        }
        if (i > 6){
            //too long name
            *otype = -4;
            free(line);
            *lexem = NULL;
            return;
        }  

        *lexem = malloc(sizeof(char) * (i+1));
        if (*lexem == NULL){
            *otype = -11;
            free(line);
            *lexem = NULL;
            return;
        }
        for (int  z = 0; z < i; ++z){
            (*lexem)[z] = line[z];
        }
        free(line);
        (*lexem)[i] = '\0';
        return;
    }
    //operator
    if ((c == '+') || (c == '*') || (c == '-') || (c == '/')){
        bracket_r = 0;
        bracket_l = 0;
        if (is_op == 1){
            *otype = -7;     
            *lexem = NULL;
            return;
        }
        is_num = 0;
        *otype = 1;
        *lexem = malloc(sizeof(char));
        if (*lexem == NULL){
            *otype = -11;
            *lexem = NULL;
            return;
        }
        **lexem = c;
        prev = getchar();
        is_op = 1;
        return;
    }
    if (c == '('){
        if (bracket_r == 1){
            *otype = -7;     
            *lexem = NULL;
            return;
        }
        bracket_l = 1;
        is_num = 0;
        balance++;
        *otype = 1;
        *lexem = malloc(sizeof(char));
        if (*lexem == NULL){
            *otype = -11;
            *lexem = NULL;
            return;
        }
        **lexem = c;
        prev = getchar();
        return;
    }
    if (c == ')'){
        if (bracket_l == 1){
            *otype = -7;     
            *lexem = NULL;
            return;
        }
        bracket_r = 1;
        balance--;
        if (balance < 0){
            *otype = -5;     
            *lexem = NULL;
            return;
        }
        is_num = 0;
        *otype = 1;
        *lexem = malloc(sizeof(char));
        if (*lexem == NULL){
            *otype = -11;
            *lexem = NULL;
            return;
        }
        **lexem = c;
        prev = getchar();
        return;
    }
    *otype = -6;
    *lexem = NULL;
}

int 
main(int argc, char **argv)
{
    Stack stack;
    stack_init(&stack);
    Polis polis;
    blank(&polis);
    int type = 0;
    char *lexem = NULL;
    char res;
    vars = NULL;
    while ((type != -1) && (type != -2) && (type != -3) && (type != -4) ){
        next1(&type, &lexem);
        if (type == -1){
            if (balance != 0){
                printf("Missing ')'\n");
                clear(&polis);
                stack_finalize(&stack);
                if (vars != NULL)
                    free_list(vars);
                return 1;
            }
            break;
        }
        if (type == -3){
            clear(&polis);
            stack_finalize(&stack);
            if (vars != NULL)
                free_list(vars);
            printf("Incorrect number input\n");
            return 1;

        }
        if (type == -4){
            clear(&polis);
            stack_finalize(&stack);
            if (vars != NULL)
                free_list(vars);
            printf("Too long variable name! Must be less than 7\n");
            return 1;
        }
        if (type == -5){
            clear(&polis);
            stack_finalize(&stack);
            if (vars != NULL)
                free_list(vars);
            printf("Missing '('\n");
            return 1;
        }
        if (type == -6){
            clear(&polis);
            stack_finalize(&stack);
            if (vars != NULL)
                free_list(vars);
            printf("Bad symbol\n");
            return 1;
        }
        if (type == -7){
            clear(&polis);
            stack_finalize(&stack);
            if (vars != NULL)
                free_list(vars);
            printf("Missing operand between operators\n");
            return 1;
        }
        if (type == -8){
            clear(&polis);
            stack_finalize(&stack);
            if (vars != NULL)
                free_list(vars);
            printf("Missing operator between operands\n");
            return 1;
        }
        if (type == -9){
            clear(&polis);
            stack_finalize(&stack);
            if (vars != NULL)
                free_list(vars);
            printf("Bad variable name\n");
            return 1;
        }
        if (type == -11){
            clear(&polis);
            stack_finalize(&stack);
            if (vars != NULL)
                free_list(vars);
            printf("Memory error\n");
            return 1;
        }

        if (type == 0){
            double a = 0;
            sscanf(lexem, "%lf", &a);
            //printf("%lf\n", a);
            free(lexem);
            char rt = sizeof(double) + sizeof(Calculate_elem);
            Calculate_elem func3 = &num_func;
            add(&polis, &rt, sizeof(char));
            add(&polis, &func3, sizeof(Calculate_elem));
            add(&polis, &a, sizeof(double));
        }
        if (type == 2){
            //printf("%s\n", lexem);
            char rt = sizeof(char)*strlen(lexem) + sizeof(Calculate_elem);
            Calculate_elem func6 = &var_func;
            add(&polis, &rt, sizeof(char));
            add(&polis, &func6, sizeof(Calculate_elem));
            for (int z = 0; z < strlen(lexem); ++z){
                add(&polis, &(lexem[z]), sizeof(char));
            }
            free(lexem);
        }
        if (type == 1){
            char a;
            a = lexem[0];
            switch (a){
                default:
                    break;
                case '*':
                    if (stack.size == 0){
                        stack_push(&stack, &a, sizeof(char));
                        break;
                    }
                    while (1){
                        int err = stack_pop(&stack, &res, sizeof(char)) ;
                        if (err == STACK_UNDERFLOW){
                            break;
                        }
                        if ((res == '*') || (res == '/')){
                            //printf("%c\n", res);
                            if (res == '*'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &multi_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                            if (res == '/'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &div_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                        } else {
                            stack_push(&stack, &res, sizeof(char));
                            break;
                        }
                    }
                    stack_push(&stack, &a, sizeof(char));
                break;
                case '/':
                    if (stack.size == 0){
                        stack_push(&stack, &a, sizeof(char));
                        break;
                    }
                    while (1){
                        int err = stack_pop(&stack, &res, sizeof(char)) ;
                        if (err == STACK_UNDERFLOW){
                            break;
                        }
                        if ((res == '*') || (res == '/')){
                            //printf("%c\n", res);
                            if (res == '*'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &multi_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                            if (res == '/'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &div_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                        } else {
                            stack_push(&stack, &res, sizeof(char));
                            break;
                        }
                    }
                    stack_push(&stack, &a, sizeof(char));
                break;
                case '+':
                    if (stack.size == 0){
                        stack_push(&stack, &a, sizeof(char));
                        break;
                    }
                    while (1){
                        int err = stack_pop(&stack, &res, sizeof(char)) ;
                        if (err == STACK_UNDERFLOW){
                            break;
                        }
                        if ((res == '*') || (res == '/') || (res == '+') || (res == '-')){
                            //printf("%c\n", res);
                            if (res == '+'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &add_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                            if (res == '-'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &sub_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                            if (res == '*'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &multi_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                            if (res == '/'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &div_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                        } else {
                            stack_push(&stack, &res, sizeof(char));
                            break;
                        }
                    }
                    stack_push(&stack, &a, sizeof(char));
                break;
                case '-':
                    if (stack.size == 0){
                        stack_push(&stack, &a, sizeof(char));
                        break;
                    }
                    while (1){
                        int err = stack_pop(&stack, &res, sizeof(char)) ;
                        if (err == STACK_UNDERFLOW){
                            break;
                        }
                        if ((res == '*') || (res == '/') || (res == '+') || (res == '-')){
                            //printf("%c\n", res);
                            if (res == '+'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &add_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                            if (res == '-'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &sub_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                            if (res == '*'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &multi_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                            if (res == '/'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &div_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                        } else {
                            stack_push(&stack, &res, sizeof(char));
                            break;
                        }
                    }
                    stack_push(&stack, &a, sizeof(char));
                break;
                case '(':
                    stack_push(&stack, &a, sizeof(char));
                break;
                case ')':
                    while (1){
                        int err = stack_pop(&stack, &res, sizeof(char)) ;
                        if (err == STACK_UNDERFLOW){
                            break;
                        }
                        if (res != '('){
                            //printf("%c\n", res);
                            if (res == '+'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &add_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                            if (res == '-'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &sub_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                            if (res == '*'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &multi_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                            if (res == '/'){
                                char rt = sizeof(char) + sizeof(Calculate_elem);
                                Calculate_elem func5 = &div_func;
                                add(&polis, &rt, sizeof(char));
                                add(&polis, &func5, sizeof(Calculate_elem));
                                add(&polis, &res, sizeof(char));
                            }
                        } else {
                            break;
                        }
                    }
                break;
            }
            free(lexem);
        }
    }
    while (stack_pop(&stack, &res, sizeof(char)) != STACK_UNDERFLOW){
       // printf("%c\n", res);
        if (res == '+'){
            char rt = sizeof(char) + sizeof(Calculate_elem);
            Calculate_elem func5 = &add_func;
            add(&polis, &rt, sizeof(char));
            add(&polis, &func5, sizeof(Calculate_elem));
            add(&polis, &res, sizeof(char));
        }
        if (res == '-'){
            char rt = sizeof(char) + sizeof(Calculate_elem);
            Calculate_elem func5 = &sub_func;
            add(&polis, &rt, sizeof(char));
            add(&polis, &func5, sizeof(Calculate_elem));
            add(&polis, &res, sizeof(char));
        }
        if (res == '*'){
            char rt = sizeof(char) + sizeof(Calculate_elem);
            Calculate_elem func5 = &multi_func;
            add(&polis, &rt, sizeof(char));
            add(&polis, &func5, sizeof(Calculate_elem));
            add(&polis, &res, sizeof(char));
        }
        if (res == '/'){
            char rt = sizeof(char) + sizeof(Calculate_elem);
            Calculate_elem func5 = &div_func;
            add(&polis, &rt, sizeof(char));
            add(&polis, &func5, sizeof(Calculate_elem));
            add(&polis, &res, sizeof(char));
        }
    }

    //цикл ввода
    stack_finalize(&stack);
    //free(init);
    char buf[1024];

    vars = NULL;
    while (fgets(buf,1024,stdin) != NULL){
        if (buf[0] == '='){
            double result;
            int err = calculate_polis(&polis, &result, sizeof(double));
            if (err != 0){
                clear(&polis);
                if (vars != NULL)
                    free_list(vars);
                if (err == 14){
                    printf("Division by 0\n");
                    return 1;
                }
                printf("Calculations error\n");
                return 1;
            }
            printf("result = %lf\n", result);
            continue;
        }
        int count = 0;
        char naming[7];
        for (int z = 0; z < 7; ++z){
            naming[z] = '\0';
        }
        char *ptr;
        while (buf[count] != '='){
            naming[count] = buf[count];
            count++;
            if (buf[count] == '=')
                ptr = &buf[count];
        }
        ptr += sizeof(char);
        //printf("%s", ptr);
        //printf("name = %s\n", naming);
        double to_write = 0;
        sscanf(ptr, "%lf",&to_write);
        //printf("nooo %lf\n", to_write);
        add_list(&vars, naming,to_write);
    }
    clear(&polis);
    if (vars != NULL)
        free_list(vars);
    return 0;
}
