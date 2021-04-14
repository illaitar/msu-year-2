#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void concat(char **res, char *str1, char *str2){
    char *result = malloc(strlen(str1) + strlen(str2) + 1);
    sprintf(result, "%s%s", str1, str2);
    free(*res);
    *res = result;
}

void err_msg(const char *msg, int code){
    if (write(2, msg, strlen(msg)) < 0)
        abort();
    exit(code);
}

void print_num(int *count, int to_do){
    int totally_useless;
    if (!to_do)
        return;
    (*count)++;
    char num[100] = {'\0'};
    sprintf(num, "%d%c", *count, ':');
    totally_useless = write(1, num, strlen(num));
    if (totally_useless)
        return;
}

void print_result(char *str_endl, char *copy){
    int totally_useless = write(1, str_endl, strlen(str_endl));
    totally_useless = write(1, copy, strlen(copy));
    totally_useless = write(1, "\n", 1);
    if (totally_useless)
        return;
}

enum {MAXLEN = 1024, V_FLAG = 1, N_FLAG = 2};

int 
main(int argc, char **argv)
{
    int v_flag = 0, n_flag = 0;
    int met_file = 0, line_pos = -1, non_flag = 0, file_pos = 0;
    for (int i = 1; i < argc; ++i){
        if (argv[i][0] == '-'){
            for (int z = 1; z < strlen(argv[i]); ++z){
                if ((argv[i][z] != 'v') && (argv[i][z] != 'n'))
                    err_msg("Wrong flag\n", 1);
                v_flag = v_flag || (argv[i][z] == 'v');
                n_flag = n_flag || (argv[i][z] == 'n');
            }
        } else {
            non_flag++;
            if (non_flag == 3)
                err_msg("Too many arguments\n", 2);
            if (met_file == 0){
                line_pos = i;
                met_file = 1;
            } else {
                file_pos = i;
            }
        }
    }
    if (line_pos == -1)
        err_msg("No arguments!\n",3);
    int fd;
    if (file_pos == 0){
        fd = 0;
    } else{
        if((fd = open(argv[file_pos], O_RDONLY))==-1){
            err_msg("File open error\n", 4);
        }
    }
    char buf[MAXLEN + 1];
    char *str_endl = malloc(sizeof(1));
    str_endl[0] = '\0';
    int n, try_to_write = 0, line_count = 0;
    while((n = read(fd, buf, MAXLEN)) > 0){
        buf[n] = '\0';
        char *to_work = buf, *pos = NULL;
        while (( pos = strchr(to_work, '\n')) != NULL){
            int len = pos - to_work;
            char *copy = malloc(sizeof(char) * (len + 1));
            strncpy(copy, to_work, len);
            copy[len] = '\0';
            char *new = strdup(copy);
            concat(&new, str_endl, copy);
            if  ((((strstr(new, argv[line_pos]) != NULL) && (v_flag == 0)) || 
                ((strstr(new, argv[line_pos]) != NULL) && (v_flag == 0)))&& (try_to_write == 0)){
                print_num(&line_count, n_flag);
                print_result(new,"\0");
            } else {
                if (((v_flag == 0) && ((try_to_write != 0) || (strstr(copy, argv[line_pos]) != 0))) 
                || ((v_flag == 1) && (try_to_write != 1) && (strstr(copy, argv[line_pos]) == 0))){
                    print_num(&line_count, n_flag);
                    print_result(str_endl, copy);
                }
                try_to_write = try_to_write * (try_to_write != 1);
            }
            free(str_endl);
            str_endl = malloc(sizeof(1));
            str_endl[0] = '\0';
            to_work = pos + 1;
            free(copy);
            free(new);
        }
        pos = buf + n;
        int len = pos - to_work;
        char *copy;
        copy = malloc(sizeof(char) * ((len >= 0) * len + 1));
        strncpy(copy, to_work, len);
        copy[len] = '\0';
        concat(&str_endl,str_endl, copy);
        try_to_write = strstr(str_endl, argv[line_pos]) != 0;
        to_work = pos + 1;
        free(copy);
    }
    if (((v_flag == 0) && (strstr(str_endl, argv[line_pos]) != 0)) ||
    ((v_flag == 1) && (strstr(str_endl, argv[line_pos]) == 0))){
        print_num(&line_count, n_flag);
        print_result(str_endl, "\0");
    }
    free(str_endl);
    close(fd);
    return 0;
}

