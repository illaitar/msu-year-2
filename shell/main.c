#include <stdio.h>
#include <unistd.h>
#include "stack.h"
#include "poliz.h"
#include "syntax.h"
#include <sys/wait.h>
int 
main(int argc, char **argv)
{
    int z = 0;
    while (z < 5){
        printf("\n=>");
        get_next_line();
        z++;
    }
    return 0;
}
