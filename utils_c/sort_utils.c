#include <stdlib.h>
#include <string.h>
#include <utils.h>
#include <sort_utils.h>

/**
 * Performs counting sort on a specific digit on an array of integers represented as strings.
 * Sorting operation modifies the input array.
 * @param a: pointer to an array of strings representing integers
 * @param len: pointer to an array of integers representing the length of corresponding string in a
 * @param n: # of elements in a and len
 * @param pos: digit by which the integers are sorted, 0 is last, 1 is second to last and so on
 */
void counting_sort(big_int *a, int n, int pos){
    int counter[10] = {0}; //initialize counter with zeros
    int digit[n]; //array representing digits to be sorted
    // count the occurrences of each digit
    for(int i = 0; i < n; ++i){
        // prepare a histogram of key frequencies
        // len[i] is length and len[i] - 1 is the index of the last element
        // check if a digit at index len - 1 - pos exists
        int idx_at_pos = (int)a[i].len - 1 - pos;
        if(idx_at_pos >= 0){
            char temp_digit[2] = {'\0'};
            // len[i] is length and len[i] - 1 is the index of the last element
            temp_digit[0] = a[i].num[idx_at_pos];
            digit[i] = atoi(temp_digit);
        } else digit[i] = 0;
        ++counter[digit[i]];
    }
    // calculate prefix sums
    for(int i = 1; i < 10; ++i){
        counter[i] += counter[i - 1];
    }
    big_int result[n];
    for(int i = n - 1; i >= 0; --i){
        --counter[digit[i]];
        result[counter[digit[i]]] = a[i];
    }
    for(int i = 0; i < n; ++i) a[i] = result[i];
}

/**
 * Performs radix sort on an array of integers represented by strings.
 * @param a: an array of pointers to strings representing integers
 * @param n: # of elements in a
 * @returns pointer to an array of sorted integers represented as strings
 */
void radix_sort(big_int *a, int n, size_t max_int_len){
    // from least significant to most significant digit (right to left)
    for(int i = 0; i < max_int_len; ++i){
        //perform counting sort on a digit at ith position
        counting_sort(a, n, i);
        //print_str_array((char **)result, n);
    }
}
