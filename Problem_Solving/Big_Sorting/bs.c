#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <utils.h>
#include <sort_utils.h>

int main(void){
    char* input = get_line();
    // number of elements to be sorted
    int no_elem = read_int(input);
    free(input);
    printf("\n# of elements to be sorted: %d\n", no_elem);

    clock_t start, end;
    double time_elapsed;
    
    char *integers[no_elem];
    int len[no_elem];
    start = clock();
    for(int i = 0; i < no_elem; ++i){
        integers[i] = get_line();
        len[i] = strlen(integers[i]) - 1; //-1 to account for \n
        //printf("%s: %d\n", integers[i], len[i]);
    }
    end = clock();
    time_elapsed = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Time elapsed on reading input: %d seconds\n", time_elapsed);
    
    int max_int_len = len[max_array((int *)len, no_elem)];
    start = clock();
    radix_sort((char **)integers, (int *) len, no_elem, max_int_len);
    end = clock();
    time_elapsed = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Time elapsed on radix sort: %d seconds\n", time_elapsed);
}
