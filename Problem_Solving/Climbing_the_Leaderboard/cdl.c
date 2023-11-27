#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

int main(){
   
    //the # of players
    char *input_line = get_line();
    int n = read_int(input_line); 
    free(input_line);

    exit(EXIT_SUCCESS);
}
