#ifndef SKIPP
#define SKIPP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Skip{
    struct Skip *next;
    int flag;
    int value;
    int cur_bal;
} Skip;



typedef Skip *Skips;

typedef struct global{
    Skips skips;
    int pipe_in;
    int status;
    int active_list;
    int free_ride;
    int my_stdout[2];
    int cur_type;
    int logic_res;
    //1 - var
    //2 - || or &&
    //3 - < > >>
    int re;
    int wr;
} Global;

 void add_list(Skip **root, int bal);

void free_list(Skip *root);

void print_list(Skips root);

void add_one(Skip **root);

void toggle_off(Skip **root, int bal);
#endif
