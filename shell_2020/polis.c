#include "poliz.h"

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include "skips.h"
#include <errno.h>
#include <unistd.h>
#include "skips.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>

char **separate2(char *str1, int *argc){
    char **argv1 = malloc(sizeof(char *));
    int argc1 = 0;
    while(*str1 == ' '){
        str1++;
    }
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

    if (!((strcmp(prev, " ") == 0) ||(strlen(prev) == 0))){
        argv1 = realloc(argv1, sizeof(char *) * (argc1 + 1));
        char *darwin =  strdup(prev);
        argv1[argc1] = darwin;
        argc1++;
    }
    argv1 = realloc(argv1, sizeof(char *) * (argc1 + 1));
    argv1[argc1] = NULL;
    argc1++;
    *argc = argc1;

    //~ for (int z = 0; z < argc1; ++z){
        //~ fprintf(stderr,"argv = %s\n", argv1[z]);
    //~ }
    return argv1;
}

#define SAFE(call) 	do { \
	                    flag = call; \
                        if ((flag < 100) && (flag != 0)) { \
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

int free_everyone(const Polis *pol, void *resp, size_t size_res, Skips s){
    Global param;
    param.skips = s;
    param.pipe_in = -1;
    param.status = 0;
    param.active_list = 0;
    param.free_ride = 0;
    param.logic_res = 0;
    param.re = -1;
    param.wr = -1;
    param.free_ride = 1;
	Stack stack;
	int flag = stack_init(&stack);
	if (flag != 0)
		return flag;
	for (size_t curr_size = 0; curr_size < pol->size; curr_size += sizeof (Size_elem) + ((char *)pol->data)[curr_size] ) {
		void *elem = &((char *)pol->data)[curr_size + sizeof (Size_elem)];
		Calculate_elem func;
		memcpy(&func, elem, sizeof(Calculate_elem));
		func(elem, ((char *)pol->data)[curr_size], &stack, &param);
	}
	stack_finalize(&stack);
    return 0;
}

int
calculate_polis(const Polis *pol, void *resp, size_t size_res, Skips s, Stack *why)
{
    Global param;
    param.skips = s;
    param.pipe_in = -1;
    param.status = 0;
    param.active_list = 0;
    param.free_ride = 0;
    param.logic_res = 0;
    param.re = -1;
    param.wr = -1;
    pipe(param.my_stdout);
    int flag = 0;
    //main cycle
	for (size_t curr_size = 0; curr_size < pol->size; curr_size += sizeof (Size_elem) + ((char *)pol->data)[curr_size] ) {
		void *elem = &((char *)pol->data)[curr_size + sizeof (Size_elem)];
		Calculate_elem func;
		memcpy(&func, elem, sizeof(Calculate_elem));
		SAFE(func(elem, ((char *)pol->data)[curr_size], why, &param));
	}
    if (param.cur_type == 1){
        char *str1;
        stack_pop(why, &str1, sizeof(char *));
        int argc1;
        pid_t pid;
        char **argv1 = separate2(str1, &argc1);
        if (argv1[0][strlen(argv1[0]) - 1] == ' '){
            argv1[0][strlen(argv1[0]) - 1] = '\0';
        }
        if (param.pipe_in == -1){
            char buf[1024];
            int n;
            close(param.my_stdout[1]);
            while((n = read(param.my_stdout[0], buf, 1024)) > 0)
            if(write(1, buf, n) == -1) return 1;
            close(param.my_stdout[0]);
            if ((pid = fork())== 0){
                execvp(argv1[0], argv1); 
                perror(argv1[0]);
                exit(1);
            }
            int status;
            for (int z = 0; z < argc1; ++z)
                free(argv1[z]);
            free(argv1);
            waitpid(pid, &status, 0);
        } else {
            char buf[1024];
            int n;
            close(param.my_stdout[1]);
            while((n = read(param.my_stdout[0], buf, 1024)) > 0)
            if(write(1, buf, n) == -1) return 1;
            close(param.my_stdout[0]);
            int prev_pipe = param.pipe_in;
            pid_t pid;

            if ((pid = fork())== 0){
                dup2(prev_pipe, 0);
                close(prev_pipe);
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
            int status;
            waitpid(pid, &status, 0);
            close(prev_pipe);
            //fprintf(stderr, "NOOOOOO\n");
        }


    }
    if (param.cur_type == 2){
        char buf[1024];
        int n;
        close(param.my_stdout[1]);
        while((n = read(param.my_stdout[0], buf, 1024)) > 0)
        if(write(1, buf, n) == -1) return 1;
        close(param.my_stdout[0]);
    }
    if ((param.cur_type == 3) || (param.cur_type == 4)){
        char *str1;
        stack_pop(why, &str1, sizeof(char *));
        int argc1;
        char **argv1 = separate2(str1, &argc1);
        if (argv1[0][strlen(argv1[0]) - 1] == ' '){
            argv1[0][strlen(argv1[0]) - 1] = '\0';
        }
        pid_t pid;
        int flag = 0;
        flag = 0;
        int prev_pipe;
        if (param.pipe_in != -1){
            prev_pipe = param.pipe_in;
            flag = 1;
        }
        if (param.re != -1){

            if (flag == 1){
                close(prev_pipe);
            }
            prev_pipe = param.re;
            param.re = -1;
            flag = 1;
        }
        int flag2 = 0;
        int next_pipe;
        if (param.wr != -1){
            flag2 = 1;
            next_pipe = param.wr;
            param.wr = -1;
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
        for (int z = 0; z < argc1; ++z)
            free(argv1[z]);
        free(argv1);
        int status;
        waitpid(pid, &status, 0);
    }

    //all is ok
    flag = 0;
    goto FINALLY;

FINALLY:
    //free everything
    param.free_ride = 1;
	for (size_t curr_size = 0; curr_size < pol->size; curr_size += sizeof (Size_elem) + ((char *)pol->data)[curr_size] ) {
		void *elem = &((char *)pol->data)[curr_size + sizeof (Size_elem)];
		Calculate_elem func;
		memcpy(&func, elem, sizeof(Calculate_elem));
        func(elem, ((char *)pol->data)[curr_size], why, &param);
	}
	stack_finalize(why);
	return flag;

}
