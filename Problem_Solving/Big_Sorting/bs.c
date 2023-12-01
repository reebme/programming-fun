#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>
#include <sort_utils.h>

int main(void){
    char* input = get_line();
    // number of elements to be sorted
    int no_elem = read_int(input);
    free(input);
    printf("\n# of elements to be sorted: %d\n", no_elem);

    char *integers[no_elem];
    int len[no_elem];
    for(int i = 0; i < no_elem; ++i){
        integers[i] = get_line();
        len[i] = strlen(integers[i]) - 1; //-1 to account for \n
        //printf("%s: %d\n", integers[i], len[i]);
    }
    int max_int_len = len[max_array((int *)len, no_elem)];
    radix_sort((char **)integers, (int *) len, no_elem, max_int_len);
}
