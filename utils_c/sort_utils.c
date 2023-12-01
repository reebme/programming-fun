#include <stdlib.h>
#include <string.h>
#include <utils.h>
#include <sort_utils.h>

/**
 * Performs counting sort on a specific digit on an array of integers represented as strings.
 * @param a: pointer to an array of strings representing integers
 * @param len: pointer to an array of integers representing the length of corresponding string in a
 * @param n: # of elements in a and len
 * @param pos: digit by which the integers are sorted, 0 is last, 1 is second to last and so on
 * @returns pointer to an array of sorted integers represented by strings
 */
char *counting_sort(char **a, int *len, int n, int pos){
    int counter[10] = {0}; //or memset with 0
    // count the occurrences of each digit
    for(int i = 0; i < n; ++i){
        if(len[i] - pos - 1 > 0){
            char digit[2] = {'\0'};
            digit[0] = a[i][len[i] - pos - 1];
            ++counter[atoi(digit)];
        }
    }
    print_array(10, counter);
}

/**
 * Performs radix sort on an array of integers represented by strings.
 * @param a: an array of strings representing integers
 * @param n: # of elements in a
 * @param max_int_len: max length of integer in the array a
 * @returns pointer to an array of sorted integers represented by strings
 */
char *radix_sort(char **a, int *len, int n, int max_int_len){
    // from least significant to most significant digit
    for(int i = 0; i < max_int_len; ++i){
        counting_sort(a, len, n, i);
    }
}
