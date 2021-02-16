#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "poliz.h"
#include "float.h"
#include <unistd.h>
#include "skips.h"
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <signal.h>

#define RES_TYPE(p, b) if (res == p){ \
                                char rt = sizeof(char) + sizeof(Calculate_elem);\
                                Calculate_elem func5 = &b;\
                                add(&polis, &rt, sizeof(char));\
                                add(&polis, &func5, sizeof(Calculate_elem));\
                                add(&polis, &res, sizeof(char));\
                            } 

#define ERR_MSG(c,msg)            if (type == c){\
  clear(&polis);\
            stack_finalize(&stack);\
            free_list(skip_table);\
            printf("msg\n");\
            exit -c;\
        }

#define    CASE_CONSTRUCT(cond,types)             if (stack.size == 0){\
                        stack_push(&stack, &a, sizeof(char));\
                        break;\
                    }\
                    while (1){\
                        int err = stack_pop(&stack, &res, sizeof(char)) ;\
                        if (err == STACK_UNDERFLOW){\
                            break;\
                        }\
                        if (cond){\
                            types\
                        } else {\
                            stack_push(&stack, &res, sizeof(char));\
                            break;\
                        }\
                    } \
                    stack_push(&stack, &a, sizeof(char));\

                            /* printf("%c", res); */

#define priority_2 CASE_CONSTRUCT((res == '<') || (res == '%') || (res == '>') || (res == '@') || (res == '^') || (res =='|') || (res ==')'), RES_TYPE('<',left_func);RES_TYPE('>',right_func);RES_TYPE('%',append);RES_TYPE('|',or_func);RES_TYPE('@',skip_func2);RES_TYPE('^',skip_func);RES_TYPE(')',bracket););

#define priority_3 CASE_CONSTRUCT((res == '<') || (res == '%') || (res == '>') || (res =='|')|| (res ==')'), RES_TYPE('<',left_func);RES_TYPE('>',right_func);RES_TYPE('%',append);RES_TYPE('|',or_func);RES_TYPE(')',bracket););

#define priority_4 CASE_CONSTRUCT((res == '<') || (res == '%') || (res == '>')|| (res ==')'), RES_TYPE('<',left_func);RES_TYPE('>',right_func);RES_TYPE('%',append);RES_TYPE(')',bracket););

int fd[2];

void sig(int s){
    Polis *pol;
    Skips list;
    Stack *wat;
    read(fd[0], &pol, sizeof(pol));
    read(fd[0], &list, sizeof(list));
    read(fd[0], &wat, sizeof(wat));
    Stack stack = *wat;
    Polis polis = *pol;
    close(fd[0]);
    close(fd[1]);
    int result = 0;
    free_everyone(&polis, &result, sizeof(double), list);
    free_list(list);
    clear(&polis);
    stack_finalize(&stack);
    kill(getpid(), SIGKILL);
}

char **separate(char *str1, int *argc){
    char **argv1 = malloc(sizeof(char *));
    int argc1 = 0;
    char *start = str1;
    char *prev = str1;
    char *cur = start;
    int len;
    while ((cur = strstr(cur, " ") ) != NULL){
        cur++;
        len = cur - prev;
        if (len <= 1){
            prev = cur;
            continue;
        }
        char *darwin = malloc(sizeof(char)*(len+1));
        strncpy(darwin, cur - len, len);
        darwin[len] = '\0';
        argv1 = realloc(argv1, sizeof(char *) * (argc1 + 1));
        argv1[argc1] = darwin;
        prev = cur;
        argc1++;
    }
    argv1 = realloc(argv1, sizeof(char *) * (argc1 + 2));
    if (!((strcmp(prev, " ") == 0) ||(strlen(prev) == 0))){
        char *darwin =  strdup(prev);
        argv1[argc1] = darwin;
        argc1++;
    }
    argv1[argc1] = NULL;
    *argc = argc1;
    //~ for (int z = 0; z < argc1; ++z){
        //~ fprintf(stderr,"argv = %s\n", argv1[z]);
    //~ }
    return argv1;
}

typedef struct local{
    int balance;
    char prev;
    int is_op;
    int is_num;
    int bracket_l;
    int bracket_r;
    int fon;
} local;

int
var_func(const void *elem, Size_elem size, Stack *stack, Global *param)
{

    if (param->free_ride == 1){
        char **str = (char**)((char *)elem + sizeof(Calculate_elem));
        free(*str);
        return 0;
    }
    if (param->status > 0){
        param->status -=1;

        return 0;
    } else {
        param->cur_type = 1;
    }
    char **str = (char**)((char *)elem + sizeof(Calculate_elem));
    stack_push(stack, str, sizeof(char*));
    return 0;
}



int
skip_func2(const void *elem, Size_elem size, Stack *stack,  Global *param)
{
    if (param -> free_ride == 1){
        return 0;
    }
    if (param->status > 0){
        param->active_list ++;
        param->status -=1;
        return 0;
    }  else {
        param -> cur_type = 2;
    }
    char *str1;
    if (stack->size == 0){
        if (param -> logic_res == 0){
            Skips find = param -> skips;
            for (int z = 0; z < param->active_list; ++z)
                find = find->next;
            param -> status = find ->value;
            param->active_list ++;
            return 0;
        } else {
            return 0;
        }
    }
    stack_pop(stack, &str1, sizeof(char *));
    int argc1, status;
    pid_t pid;
    char **argv1 = separate(str1, &argc1);
    if (argv1[0][strlen(argv1[0]) - 1] == ' '){
        argv1[0][strlen(argv1[0]) - 1] = '\0';
    }
    int flag = 0;
    flag = 0;
    int prev_pipe;
    if (param-> pipe_in != -1){
        prev_pipe = param->pipe_in;
        flag = 1;
    }
    if (param-> re != -1){
        if (flag == 1){
            close(prev_pipe);
        }
        prev_pipe = param -> re;
        param -> re = -1;
        flag = 1;
    }
    int flag2 = 0;
    int next_pipe;
    if (param -> wr != -1){
        flag2 = 1;
        next_pipe = param->wr;
        param -> wr = -1;
    }

    if ((pid = fork())== 0){
        if (flag == 1){
            dup2(prev_pipe, 0);
            close(prev_pipe);
        }
        if (flag2 != 1){
            dup2(param->my_stdout[1],  1);
            close(param->my_stdout[0]);
            close(param->my_stdout[1]);
        } else {
            dup2(next_pipe,  1);
            close(next_pipe);
        }
        execvp(argv1[0], argv1); 
        perror(argv1[0]);
        for (int z = 0; z < argc1; ++z)
            free(argv1[z]);
        free(argv1);
        exit(1);
    }
    for (int z = 0; z < argc1; ++z)
        free(argv1[z]);
    free(argv1);
    waitpid(pid, &status, 0);
    param -> logic_res = (status == 0);
    if (status != 0){
        Skips find = param -> skips;
        for (int z = 0; z < param->active_list; ++z)
            find = find->next;
        param -> status = find ->value;
        param->active_list ++;
    }
    return 0;
}


int
skip_func(const void *elem, Size_elem size, Stack *stack,  Global *param)
{
    if (param -> free_ride == 1){
        return 0;
    }
    if (param->status > 0){
        param->active_list ++;
        param->status -=1;
        return 0;
    }  else {
        param -> cur_type = 2;
    }
    char *str1;
    if (stack->size == 0){
        if (param -> logic_res == 0){
            return 0;
        } else {
            Skips find = param -> skips;
            for (int z = 0; z < param->active_list; ++z)
                find = find->next;
            param -> status = find ->value;
            param->active_list ++;
            return 0;
        }
    }
    stack_pop(stack, &str1, sizeof(char *));
    int argc1, status;
    pid_t pid;
    char **argv1 = separate(str1, &argc1);
    if (argv1[0][strlen(argv1[0]) - 1] == ' '){
        argv1[0][strlen(argv1[0]) - 1] = '\0';
    }
    int flag = 0;
    flag = 0;
    int prev_pipe;
    if (param-> pipe_in != -1){
        prev_pipe = param->pipe_in;
        flag = 1;
    }
    if (param-> re != -1){
        if (flag == 1){
            close(prev_pipe);
        }
        prev_pipe = param -> re;
        param -> re = -1;
        flag = 1;
    }
    int flag2 = 0;
    int next_pipe;
    if (param -> wr != -1){
        flag2 = 1;
        next_pipe = param->wr;
        param -> wr = -1;
    }

    if ((pid = fork())== 0){
        if (flag == 1){
            dup2(prev_pipe, 0);
            close(prev_pipe);
        }
        if (flag2 != 1){
            dup2(param->my_stdout[1],  1);
            close(param->my_stdout[0]);
            close(param->my_stdout[1]);
        } else {
            dup2(next_pipe,  1);
            close(next_pipe);
        }
        execvp(argv1[0], argv1); 
        perror(argv1[0]);
        for (int z = 0; z < argc1; ++z)
            free(argv1[z]);
        free(argv1);
        exit(1);
    }
    for (int z = 0; z < argc1; ++z)
        free(argv1[z]);
    free(argv1);
    waitpid(pid, &status, 0);
    param -> logic_res = (status == 0);
    if (status == 0){
        Skips find = param -> skips;
        for (int z = 0; z < param->active_list; ++z)
            find = find->next;
        param -> status = find ->value;
        param->active_list ++;
    }
    return 0;
}


int
or_func(const void *elem, Size_elem size, Stack *stack,  Global *param)
{
    if (param -> free_ride == 1)
        return 0;
    if (param->status > 0){
        param->status -=1;
        return 0;
    }
    char *str1;

    if (stack -> size == 0){
            int fd[2];
            pipe(fd);
            param -> pipe_in = fd[0];
            char buf[1024];
            int n;
            close(param->my_stdout[1]);
            while((n = read(param->my_stdout[0], buf, 1024)) > 0)
            if(write(fd[1], buf, n) == -1) return 1;
            close(fd[1]);
            close(param->my_stdout[0]);

            int new_std[2];
            if(pipe(new_std) == -1) return 1;
            param->my_stdout[0] = new_std[0];
            param->my_stdout[1] = new_std[1];
        return 0;
    }
    stack_pop(stack, &str1, sizeof(char *));
    int argc1;
    char **argv1 = separate(str1, &argc1);
    if (argv1[0][strlen(argv1[0]) - 1] == ' '){
        argv1[0][strlen(argv1[0]) - 1] = '\0';
    }
    int fd[2];
    int prev_pipe;
    int flag = 0;
    pipe(fd);
    flag = 0;
    if (param-> pipe_in == -1){
        param -> pipe_in = fd[0];
    } else {
        prev_pipe = param->pipe_in;
        flag = 1;
    }
    if (param-> re != -1){
        if (flag == 1){
            close(param -> pipe_in);
        }
        prev_pipe = param -> re;
        param->re = -1;
        param -> pipe_in = -1;
    }
    int flag2 = 0;
    int next_pipe;
    if (param-> wr != -1){
        next_pipe = param->wr;
        param->wr = -1;
        flag2 = 1;
    }
    pid_t pid;
    if ((pid = fork())== 0){
        if (flag == 1) {
            dup2(prev_pipe, 0);
            close(prev_pipe);
        }
        if (flag2 == 0){
            dup2(fd[1],1);
            close(fd[0]);
            close(fd[1]);
        } else {
            dup2(next_pipe,1);
            close(next_pipe);
        }
        execvp(argv1[0], argv1); 
        for (int z = 0; z < argc1; ++z)
            free(argv1[z]);
        free(argv1);
        perror(argv1[0]);
        exit(1);
    }
    int status;
    for (int z = 0; z < argc1; ++z)
        free(argv1[z]);
    free(argv1);
    waitpid(pid, &status, 0);
    if (flag == 1){
        close(prev_pipe);
    }
    close(fd[1]);
    param->pipe_in = fd[0];
    return 0;
}


int
left_func(const void *elem, Size_elem size, Stack *stack,  Global *param)
{
    if (param -> free_ride == 1)
        return 0;
    if (param->status > 0){
        param->status -=1;
        return 0;
    } else {
        param->cur_type = 3;
    }
    char *str1;
    stack_pop(stack, &str1, sizeof(char *));
    int fd1;
    if((fd1=open(str1,O_RDONLY))==-1){
        fprintf(stderr,"error with file");
        return -1; 
    }
    if (stack -> size == 0){
        //this is not realized  :((((
        return 1;
    }
    param -> re = fd1;
    return 0;
}

int
right_func(const void *elem, Size_elem size, Stack *stack,  Global *param)
{
    if (param -> free_ride == 1)
        return 0;
    if (param->status > 0){
        param->status -=1;
        return 0;
    } else {
        param->cur_type = 4;
    }
    char *str1;
    stack_pop(stack, &str1, sizeof(char *));
    int fd1;
    if((fd1=open(str1, O_WRONLY|O_TRUNC|O_CREAT, 0644))==-1){
        fprintf(stderr,"error with file");
        return -1; 
    }
    if (stack -> size == 0){
        char buf[1024];
        int n;
        close(param->my_stdout[1]);
        while((n = read(param->my_stdout[0], buf, 1024)) > 0)
        if(write(fd1, buf, n) == -1) return 1;
        close(fd1);
        close(param->my_stdout[0]);
        int new_std[2];
        if(pipe(new_std) == -1) return 1;
        param->my_stdout[0] = new_std[0];
        param->my_stdout[1] = new_std[1];
        return 1;
    }
    param -> wr = fd1;
    return 0;
}

int
append(const void *elem, Size_elem size, Stack *stack,  Global *param)
{
    if (param -> free_ride == 1)
        return 0;
    if (param->status > 0){
        param->status -=1;
        return 0;
    } else {
        param->cur_type = 4;
    }
    char *str1;
    stack_pop(stack, &str1, sizeof(char *));
    int fd1;
    if((fd1=open(str1, O_WRONLY|O_APPEND|O_CREAT, 0644))==-1){
        fprintf(stderr,"error with file");
        return -1; 
    }
    if (stack -> size == 0){
        char buf[1024];
        int n;
        close(param->my_stdout[1]);
        while((n = read(param->my_stdout[0], buf, 1024)) > 0)
        if(write(fd1, buf, n) == -1) return 1;
        close(fd1);
        close(param->my_stdout[0]);
        int new_std[2];
        if(pipe(new_std) == -1) return 1;
        param->my_stdout[0] = new_std[0];
        param->my_stdout[1] = new_std[1];
        return 1;
    }
    param -> wr = fd1;
    return 0;
    //~ if (param -> free_ride == 1){
        //~ return 0;
    //~ }
    //~ //fprintf(stderr, "right right func!\n");
    //~ param ->skipped_var =0;
    //~ if (param->status > 0){
        //~ //printf("Dont\n");
        //~ param->status -=1;
        //~ return 0;
    //~ } else {
        //~ param->cur_type = 3;
    //~ }
    //~ param ->skip2_or = 0;
    //~ param->last_was_com = 1;
    //~ param ->check = 0;
    //~ char *str1, *str2;
    //~ stack_pop(stack, &str2, sizeof(char *));
    //~ stack_pop(stack, &str1, sizeof(char *));


    //~ int argc1;
    //~ char **argv1 = separate(str1, &argc1);
    //~ argv1[0][strlen(argv1[0]) - 1] = '\0';
    //~ int fd1;
    //~ if((fd1=open(str2, O_WRONLY|O_APPEND|O_CREAT, 0644))==-1){
        //~ //fprintf(stderr,"error with file 1");
        //~ return -1; 
    //~ }
    //~ param -> wr_desc = fd1;
    //~ param ->pipe_in = -1;
    //~ //printf("pipe is now -1!\n");
    //~ for (int z = 0; z < argc1; ++z){
        //~ free(argv1[z]);
    //~ }
    //~ free(argv1);
    //~ stack_push(stack, &str1, sizeof(char*));
    //~ //printf("here is = %s\n", str1);
    return 0;
}

int 
bracket(const void *elem, Size_elem size, Stack *stack,  Global *param){

    if (param->status > 0){
        param->status -=1;
        return 0;
    }

    if (param->cur_type == 4){
        char *str1;
        stack_pop(stack, &str1, sizeof(char *));
        int argc1;
        char **argv1 = separate(str1, &argc1);
        if (argv1[0][strlen(argv1[0]) - 1] == ' '){
            argv1[0][strlen(argv1[0]) - 1] = '\0';
        }
        pid_t pid;
        int flag = 0;
        flag = 0;
        int prev_pipe;
        if (param->pipe_in != -1){
            prev_pipe = param->pipe_in;
            flag = 1;
        }
        if (param->re != -1){

            if (flag == 1){
                close(prev_pipe);
            }
            prev_pipe = param->re;
            param->re = -1;
            flag = 1;
        }
        int flag2 = 0;
        int next_pipe;
        if (param->wr != -1){
            flag2 = 1;
            next_pipe = param->wr;
            param->wr = -1;
        }

        if ((pid = fork())== 0){
            if (flag == 1){
                dup2(prev_pipe, 0);
                close(prev_pipe);
            }
            if (flag2 == 1){
                dup2(next_pipe,  1);
                close(next_pipe);
            }
            execvp(argv1[0], argv1); 
            perror(argv1[0]);
            exit(1);
        }
        int status;
        waitpid(pid, &status, 0);

        for (int z = 0; z < argc1; ++z)
            free(argv1[z]);
        free(argv1);
        return 0;
    }





    if(stack->size == 0){
        return 0;
    }
    char *str1;
    stack_pop(stack, &str1, sizeof(char *));
    int argc1, status;
    pid_t pid;
    char **argv1 = separate(str1, &argc1);
    if (argv1[0][strlen(argv1[0]) - 1] == ' '){
        argv1[0][strlen(argv1[0]) - 1] = '\0';
    }
    int prev_pipe;
    int flag = 0;
    if (param-> pipe_in == -1){

    } else {
        prev_pipe = param->pipe_in;
        param -> pipe_in = -1;
        flag = 1;
    }
    if ((pid = fork())== 0){
        if (flag == 1) {
            dup2(prev_pipe, 0);
            close(prev_pipe);
        }
        dup2(param->my_stdout[1],  1);
        close(param->my_stdout[0]);
        close(param->my_stdout[1]);
        execvp(argv1[0], argv1); 
        perror(argv1[0]);
        exit(1);
    }
    waitpid(pid, &status, 0);
    return 0;
    //~ char buf[1024];
    //~ int n;
    //~ close(param->my_stdout[1]);
    //~ while((n = read(param->my_stdout[0], buf, 1024)) > 0)
    //~ if(write(1, buf, n) == -1) return 1;
    //~ close(param->my_stdout[0]);
    //~ int new_std[2];
    //~ if(pipe(new_std) == -1) return 1;
    //~ param->my_stdout[0] = new_std[0];
    //~ param->my_stdout[1] = new_std[1];
    //~ return 0;
}

void next1(int *otype, char** lexem, local *params, Skips *skip_table){
    char c;
    if (params->prev == '\0'){
        while(((c = getchar()) == ' ')&&(c != '\n')&&(c != EOF))
           c = getchar();
        if ((c == '\n') || (c == EOF)){
            *otype = -1;
            params->is_op = 0;
            *lexem = NULL;
            return;
        }
    } else {
        c = params->prev;
        while((c == ' ')&&(c != '\n') && (c != EOF))
            c = getchar();
        if ((c == '\n') || (c == EOF)){
            *otype = -1;
            params->is_op = 0;
            *lexem = NULL;
            return;
        }
    }
    //variable
    if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || (c =='/')|| (c =='.')|| ((c >= '0') && (c <= '9'))){
        add_one(skip_table);
        params->bracket_r = 0;
        params->bracket_l = 0;
        char *line = malloc(sizeof(char)*1024);
        if (line == NULL){
            *otype = -11;
            free(line);
            *lexem = NULL;
            return;
        }
        int cur_size = 1024;
        *otype = 2;
        params->is_num = 1;
        params->is_op = 0;
        int i = 1;
        line[0] = c;
        while( ((c = getchar()) != '\n') &&  (c != EOF) && (((c >= '0') && (c <= '9')) || (c == '_') || (c =='/') || (c =='-') || (c =='.') || (  ((c >= 'A') && (c <= 'Z')) || (c == ' ') || ((c >= 'a') && (c <= 'z'))))){ 
            line[i] = c;
            i++;
            if (i == cur_size)
                line = realloc(line, sizeof(char)*((cur_size + 1024)));
        }
        params->prev = c;
        if (!( (c == '&') || (c == '@') || (c == '|') || (c == '(') || (c == ')') || (c == '\n') || (c == EOF) || (c =='-') || (c == '>') || (c == '<'))){
            *otype = -9;   
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
        for (int  z = 0; z < i; ++z)
            (*lexem)[z] = line[z];
        free(line);
        (*lexem)[i] = '\0';
        return;
    }
    //operator
    if ((c == '+') || (c == '@') || (c == '&') || (c == '|') || (c == '>') || (c == '<')){

        params->bracket_r = 0;
        params-> bracket_l = 0;
        if (params->is_op == 1){
            *otype = -7;     
            *lexem = NULL;
            return;
        }
        params->is_num = 0;
        *otype = 1;
        *lexem = malloc(sizeof(char));
        if (*lexem == NULL){
            *otype = -11;
            *lexem = NULL;
            return;
        }

        params->prev = getchar();
        
        if ((((c == '&') && (params->prev != '&'))) || ((c != '&') && (params->prev == '&') )){
            params->fon = 1;
        }
        if (((c == '&') && (params->prev == '&')) || ((c == '|') && (params->prev == '|'))){
            toggle_off(skip_table, params->balance);
        }
        add_one(skip_table);
        if ((c == '&') && (params->prev == '&')){
                c = '@';
                add_list(skip_table,params->balance);
                params->prev = getchar();
        } else {
            if ((c == '|') && (params->prev == '|')){
                c = '^';
                add_list(skip_table,params->balance);
                params->prev = getchar();
            } else {
                if ((c == '>') && (params->prev == '>')){
                    c = '%';

                    params->prev = getchar();
                } 
            }
        }
        **lexem = c;
        params->is_op = 1;
        return;
    }
    if (c == '('){
        if (params->bracket_r == 1){
            *otype = -7;     
            *lexem = NULL;
            return;
        }
        params->bracket_l = 1;
        params->is_num = 0;
        params->balance++;
        *otype = 1;
        *lexem = malloc(sizeof(char));
        if (*lexem == NULL){
            *otype = -11;
            *lexem = NULL;
            return;
        }
        **lexem = c;
        params->prev = getchar();
        return;
    }
    if (c == ')'){

        if (params->bracket_l == 1){
            *otype = -7;     
            *lexem = NULL;
            return;
        }
        params->bracket_r = 1;
        params->balance--;
        toggle_off(skip_table, params->balance);
        if (params->balance < 0){
            *otype = -5;     
            *lexem = NULL;
            return;
        }
        params->is_num = 0;
        *otype = 1;
        *lexem = malloc(sizeof(char));
        if (*lexem == NULL){
            *otype = -11;
            *lexem = NULL;
            return;
        }
        **lexem = c;
        params->prev = getchar();
        return;
    }
    *otype = -6;
    *lexem = NULL;
}



int 
get_next_line()
{

    int empty = 1;
    Skips skip_table = NULL;
    local params = {0, '\0', 0, 0, 0, 0, 0};
    Stack stack;
    stack_init(&stack);
    Polis polis;
    blank(&polis);
    int type = 0;
    char *lexem = NULL;
    char res;
    while ((type != -1) && (type != -2) && (type != -3) && (type != -4) ){
        next1(&type, &lexem, &params, &skip_table);
        if (type == -1){
            if (params.balance != 0){
                //printf("Missing ')'\n");
                return 1;
            }
            break;
        }
        empty = 0;
        ERR_MSG(-3, "Incorrect number input\n");
        ERR_MSG(-5, "Missing '('\n");
        ERR_MSG(-6, "Bad symbol\n");
        ERR_MSG(-8, "Missing operator between operands\n");
        ERR_MSG(-9, "Bad variable name\n");
        ERR_MSG(-11, "Memory error\n");
        if (type == 2){

            Calculate_elem func6 = &var_func;
            char rt = sizeof(Calculate_elem) + sizeof(lexem);
            add(&polis, &rt, sizeof(char));
            add(&polis, &func6, sizeof(Calculate_elem));
            add(&polis, &lexem, sizeof(lexem));
            //printf("%s", lexem); 
        }
        if (type == 1){
            char a = lexem[0];
            switch (a){
                default:
                    break;
                case '<':
                    priority_4
                break;
                case '>':
                    priority_4
                break;
                case '%':
                    priority_4
                break;
                case '|':
                   if (stack.size == 0){
                        res = a;
                        //printf("%c", a);
                        char rt = sizeof(char) + sizeof(Calculate_elem);
                        Calculate_elem func5 = &or_func;
                        add(&polis, &rt, sizeof(char));
                        add(&polis, &func5, sizeof(Calculate_elem));
                        add(&polis, &res, sizeof(char));
                        break;
                    }
                    while (1){
                        int err = stack_pop(&stack, &res, sizeof(char)) ;
                        if (err == STACK_UNDERFLOW)
                            break;
                        if (res != '('){
                            //printf("%c", res); 
                            RES_TYPE('@',skip_func2);
                            RES_TYPE('|',or_func);
                            RES_TYPE('^',skip_func);
                            RES_TYPE('<',left_func);
                            RES_TYPE('>',right_func);
                            RES_TYPE('%',append);
                            RES_TYPE(')',bracket);
                        } else {
                            stack_push(&stack, &res, sizeof(char));
                            break;
                        }
                    }
                    res = a;
                    //printf("%c", a);
                    char rt = sizeof(char) + sizeof(Calculate_elem);
                    Calculate_elem func5 = &or_func;
                    add(&polis, &rt, sizeof(char));
                    add(&polis, &func5, sizeof(Calculate_elem));
                    add(&polis, &res, sizeof(char));
                break;
                case '@':
                   if (stack.size == 0){
                        res = a;
                        //printf("%c", a);
                        char rt = sizeof(char) + sizeof(Calculate_elem);
                        Calculate_elem func5 = &skip_func2;
                        add(&polis, &rt, sizeof(char));
                        add(&polis, &func5, sizeof(Calculate_elem));
                        add(&polis, &res, sizeof(char));
                        break;
                    }
                    while (1){
                        int err = stack_pop(&stack, &res, sizeof(char)) ;
                        if (err == STACK_UNDERFLOW)
                            break;
                        if (res != '('){
                            //printf("%c", res); 
                            RES_TYPE('@',skip_func2);
                            RES_TYPE('|',or_func);
                            RES_TYPE('^',skip_func);
                            RES_TYPE('<',left_func);
                            RES_TYPE('>',right_func);
                            RES_TYPE('%',append);
                            RES_TYPE(')',bracket);
                        } else {
                            stack_push(&stack, &res, sizeof(char));
                            break;
                        }
                    }
                    res = a;
                    //printf("%c", a);
                    rt = sizeof(char) + sizeof(Calculate_elem);
                    func5 = &skip_func2;
                    add(&polis, &rt, sizeof(char));
                    add(&polis, &func5, sizeof(Calculate_elem));
                    add(&polis, &res, sizeof(char));
                break;
                case '^':
                   if (stack.size == 0){
                        res = a;
                        //printf("%c", a);
                        char rt = sizeof(char) + sizeof(Calculate_elem);
                        Calculate_elem func5 = &skip_func;
                        add(&polis, &rt, sizeof(char));
                        add(&polis, &func5, sizeof(Calculate_elem));
                        add(&polis, &res, sizeof(char));
                        break;
                    }
                    while (1){
                        int err = stack_pop(&stack, &res, sizeof(char)) ;
                        if (err == STACK_UNDERFLOW)
                            break;
                        if (res != '('){
                            //printf("%c", res); 
                            RES_TYPE('@',skip_func2);
                            RES_TYPE('|',or_func);
                            RES_TYPE('^',skip_func);
                            RES_TYPE('<',left_func);
                            RES_TYPE('>',right_func);
                            RES_TYPE('%',append);
                            RES_TYPE(')',bracket);
                        } else {
                            stack_push(&stack, &res, sizeof(char));
                            break;
                        }
                    }
                    res = a;
                    //printf("%c", a);
                    rt = sizeof(char) + sizeof(Calculate_elem);
                    func5 = &skip_func;
                    add(&polis, &rt, sizeof(char));
                    add(&polis, &func5, sizeof(Calculate_elem));
                    add(&polis, &res, sizeof(char));
                break;
                case '(':
                    stack_push(&stack, &a, sizeof(char));
                break;
                case ')':
                   if (stack.size == 0){
                        res = a;
                        //printf("%c", a);
                        char rt = sizeof(char) + sizeof(Calculate_elem);
                        Calculate_elem func5 = &skip_func;
                        add(&polis, &rt, sizeof(char));
                        add(&polis, &func5, sizeof(Calculate_elem));
                        add(&polis, &res, sizeof(char));
                        break;
                    }
                    while (1){
                        int err = stack_pop(&stack, &res, sizeof(char)) ;
                        if (err == STACK_UNDERFLOW)
                            break;
                        if (res != '('){
                            //printf("%c", res); 
                            RES_TYPE('@',skip_func2);
                            RES_TYPE('|',or_func);
                            RES_TYPE('^',skip_func);
                            RES_TYPE('<',left_func);
                            RES_TYPE('>',right_func);
                            RES_TYPE('%',append);
                            RES_TYPE(')',bracket);
                        } else {
                            stack_push(&stack, &res, sizeof(char));
                            break;
                        }
                    }
                    res = a;
                    //printf("%c", a);
                    rt = sizeof(char) + sizeof(Calculate_elem);
                    func5 = &bracket;
                    add(&polis, &rt, sizeof(char));
                    add(&polis, &func5, sizeof(Calculate_elem));
                    add(&polis, &res, sizeof(char));
                break;
            }
            free(lexem);
        }
    }
    while (stack_pop(&stack, &res, sizeof(char)) != STACK_UNDERFLOW){
        if (res != '('){
            //printf("%c", res); 
        }
        RES_TYPE('@',skip_func2);
        RES_TYPE('|',or_func);
        RES_TYPE('^',skip_func);
        RES_TYPE('<',left_func);
        RES_TYPE('>',right_func);
        RES_TYPE('%',append);
        RES_TYPE(')',bracket);
    }

    stack_finalize(&stack);
    //print_list(skip_table);

    if (empty == 1){
        free_list(skip_table);
        clear(&polis);
        return 0;
    }
    signal(SIGINT, sig);
    int result = 0;
    pid_t fok;
    if (params.fon == 1){
        //printf("here is fon!\n");
        if ((fok = fork()) == 0){
            signal(SIGINT, sig);
            pipe(fd);
            Polis *pol = &polis;
            
            Stack stack2;
            stack_init(&stack2);
            Stack *wat = &stack2;

            write(fd[1], &pol, sizeof(pol));
            write(fd[1], &skip_table, sizeof(skip_table));
            write(fd[1], &wat, sizeof(wat));
            int err = calculate_polis(&polis, &result, sizeof(double), skip_table, &stack2);
            free_list(skip_table);
            if (err != 0){
                if (err == 14){
                    //printf("Division by 0\n");
                    exit( 1);
                }
            }
            close(fd[0]);
            close(fd[1]);
            clear(&polis);
            stack_finalize(&stack2);
            kill(getpid(), SIGKILL);
        } else {
            signal(SIGINT, SIG_DFL);
            free_everyone(&polis, &result, sizeof(double), skip_table);
            free_list(skip_table);
            clear(&polis);
        }

    }else {
        signal(SIGINT, sig);
        pipe(fd);
        Polis *pol = &polis;
        
        Stack stack2;
        stack_init(&stack2);
        Stack *wat = &stack2;

        write(fd[1], &pol, sizeof(pol));
        write(fd[1], &skip_table, sizeof(skip_table));
        write(fd[1], &wat, sizeof(wat));
        int err = calculate_polis(&polis, &result, sizeof(double), skip_table, &stack2);
        if (err != 0){
            clear(&polis);
            printf("Calculations error\n");
            return 1;
        }
        close(fd[0]);
        close(fd[1]);
        signal(SIGINT, SIG_DFL);
        free_list(skip_table);
        clear(&polis);
        
        return 0;
    }

    return result;
}
