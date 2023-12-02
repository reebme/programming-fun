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
char **counting_sort(char **a, int *len, int n, int pos){
    int counter[10] = {0}; //initialize counter with zeros
    int digit[n];
    // count the occurrences of each digit
    for(int i = 0; i < n; ++i){
        // prepare a histogram of key frequencies
        // len[i] is length and len[i] - 1 is the index of the last element
        // check if a digit at index len - 1 - pos exists
        if(len[i] - 1 - pos >= 0){
            unsigned char temp_digit[2] = {'\0'};
            // len[i] is length and len[i] - 1 is the index of the last element
            temp_digit[0] = a[i][len[i] - 1 - pos];
            digit[i] = atoi(temp_digit);
        } else digit[i] = 0;
        ++counter[digit[i]];
    }
    // calculate prefix sums
    for(int i = 1; i < 10; ++i){
        counter[i] += counter[i - 1];
    }
    char **result = (char **)malloc(n * sizeof (char *));
    for(int i = n - 1; i >= 0; --i){
        --counter[digit[i]];
        result[counter[digit[i]]] = a[i];
    }
    return result;
}

/**
 * Performs radix sort on an array of integers represented by strings.
 * @param a: an array of strings representing integers
 * @param n: # of elements in a
 * @param max_int_len: max length of integer in the array a
 * @returns pointer to an array of sorted integers represented by strings
 */
char **radix_sort(char **a, int *len, int n, int max_int_len){
    // from least significant to most significant digit
    char **result = a;
    int *result_len = len;
    char **temp;
    for(int i = 0; i < max_int_len; ++i){
        char **temp = counting_sort(result, result_len, n, i);
        if(i != 0){
            free(result);
            free(result_len);
        }
        result = temp;
        result_len = (int *)malloc(n * sizeof(int));
        for(int i = 0; i < n; ++i) result_len[i] = strlen(result[i]) - 1;
        //print_str_array((char **)result, n);
    }
    return result;
}
