#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void err_msg(const char *msg, int code){
    if (write(2, msg, strlen(msg)) < 0)
        abort();
    exit(code);
}

enum {MAXLEN = 1024};

int count_n(const char *buf, int len){
    int ans = 0;
    if (buf == NULL)
        return ans;
    for (int z = 0; z < len; ++z)
        if (buf[z] == '\n')
            ans++;
    return ans;
}

int max(int a, int b){
    return (a>b) * a + (a<=b) * b;
}

int count_lines(int fd){
    lseek(fd, 0, SEEK_SET);
    int n, ans = 0;
    char buf[MAXLEN] = {'\0'};
    while((n = read(fd,buf,MAXLEN))>0)
        ans += count_n(buf, n);
    lseek(fd, 0, SEEK_SET);
    return ans;
}

int str_to_num(char *str){
    int ans = 0;
    for (int i = 0; i < strlen(str); ++i)
        if ((str[i] >= '0') && (str[i] <= '9'))
            ans = ans * 10 + str[i] - '0';
        else
            err_msg("line count must be a number\n", 1);
    return ans;
}

int 
main(int argc, char **argv)
{
    int lines = 9, plus_flag = 0, flag_count = 0;
    int where_file = 0;
    for (int i = 1; i < argc; ++i){
        if (argv[i][0] == '-'){
            flag_count++;
            i++;
            if (i>= argc){
                err_msg("flag -n must contain number\n", 2);
            } else {
                flag_count++;
                lines = str_to_num(argv[i]) - 1;
            }
            continue;
        }
        if (argv[i][0] == '+'){
            flag_count++;
            i++;
            if (i>= argc){
                err_msg("flag +n must contain number\n", 3);
            } else {
                plus_flag = 1;
                flag_count++;
                lines = str_to_num(argv[i]) - 1;
            }
            continue;
        }
        where_file = i;
    }
    if (argc - flag_count > 2)
        err_msg("Too many arguments!\n", 4);
    int fd;
    if (argc - flag_count == 1){
        //stdin
        char fname[7] = "XXXXXX";
        fd = mkstemp(fname);
        if (fd == -1)
            err_msg("File creating error\n", 5);
        int err = unlink(fname);
        if (err != 0)
            exit(err);
        char buf[MAXLEN] = {'\0'};
        int n, z;
        while((n = read(0,buf,MAXLEN))>0)
            if ((z = write(fd,buf,n)) < 0)
                abort();
    } else {
        if((fd = open(argv[where_file], O_RDONLY))==-1)
            err_msg("File open error\n", 6);
    }
    lseek(fd, 0, SEEK_SET); 
    if (plus_flag == 1)
        lines = count_lines(fd) - lines;
    if (lines < 0){
        lines = 0;
    }
	struct stat st;
    fstat(fd, &st);
    long file_size = st.st_size;
    char buf[MAXLEN] = {'\0'};
    long cur_offset = MAXLEN, n_count= 0, write_err;
    while (1){ 
        lseek(fd, max(file_size - cur_offset, 0), SEEK_SET);
        cur_offset += MAXLEN;
        int n = read(fd, buf, MAXLEN);
        n_count += count_n(buf, n);
        if ((n_count <= lines) && (file_size - cur_offset + MAXLEN < 0)){
                lseek(fd, 0, SEEK_SET); 
                while((n = read(fd,buf,MAXLEN))>0)
                    if ((write_err = write(1,buf,n)) < 0)
                        abort();
                break;
        }
        if (n_count > lines){
            lseek(fd, max(file_size + MAXLEN - cur_offset, 0), SEEK_SET); 
            int count = 0;
            while (n_count > lines){
                if(buf[count++] == '\n')
                    n_count--;
            }
            lseek(fd, max(file_size + MAXLEN - cur_offset + count, count), SEEK_SET); 
            while((n = read(fd,buf,MAXLEN))>0)
                if ((write_err = write(1,buf,n)) < 0)
                    abort();
            break;
        }
    }
    close(fd);
    return 0;
}

