#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <utils.h>
#include <sort_utils.h>

int main(int argc, char *argv[]){
    printf("%s\n", argv[1]);
    FILE *in_file = fopen(argv[1], "r");
    char* input = get_line(in_file);
    // number of elements to be sorted
    int no_elem = read_int(input);
    free(input);
    printf("\n# of elements to be sorted: %d\n", no_elem);

    clock_t start, end;
    double time_elapsed;
    
    big_int integers[no_elem];
    size_t max_int_len = 0;
    size_t max_len_len = 0;
    start = clock();
    for(int i = 0; i < no_elem; ++i){
        integers[i].num = get_line(in_file);
        integers[i].len = rtrim(integers[i].num); // trim \n at the end
        if(max_int_len < integers[i].len)
            max_int_len = integers[i].len;
    }
    fclose(in_file);
    max_len_len = digit_no(max_int_len);
    end = clock();
    time_elapsed = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Time elapsed on reading and preprocessing input: %f seconds\n", time_elapsed);
    
    start = clock();
    if(max_int_len > 1000)
        radix_sort_with_buckets((big_int *)integers, no_elem, max_len_len);
    else radix_sort((big_int *)integers, no_elem, max_int_len);
    end = clock();
    time_elapsed = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Time elapsed on radix sort: %f \n", time_elapsed);

/*    for(int i = 0; i < no_elem; ++i){
        printf("%s\n", integers[i].num);
        free(integers[i].num);
    }*/
}
