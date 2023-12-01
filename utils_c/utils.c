#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <utils.h>

/**
 * Gets a line of input from stdin character by character.
 * A line is a sequence of characters ending with \n which is discarded.
 * @returns a pointer to the string representing a line of input
 */
char* get_line_by_char(){
    int buff_size = 0;
    char *buff = NULL;
    char c;
    int i = 0;
    /* read from input until \n is encountered */
    while((c = fgetc(stdin)) != '\n'){
        if(i == buff_size){
            if (buff_size != 0)
                buff_size = buff_size * 2;
            else buff_size = 1;
            buff = realloc(buff, buff_size);
        }
        buff[i] = c;
        ++i;
    }
    if(i == buff_size)
        buff = realloc(buff, buff_size + 1);
    buff[i] = '\0';
    return buff;
    /* The object return most likely has a tail of allocated memory after \0 which if necessary can be removed. */
}

/**
 * Gets a line of input from stdin into a buffer.
 */
char* get_line(){
    int buff_size = 256;
    char *buff = (char *)malloc(buff_size * sizeof(char));
    int line_length = 0;    //no of characters read
    char *cursor = buff;    //current position in buffer
    bool stop = false;
    //fills buffer buff and extends it if current buffer is full
    while(!stop){
        /* reads at most buff_size characters from stdin until stream empty and waits for more */
        if(buff_size == line_length + 1){
            cursor = NULL; /* important for when realloc moves buffer to a new place */
            buff_size = buff_size * 2;
            buff = (char *)realloc(buff, buff_size);
            /*
            // if realloc fails buffer content already read is not lost
            // it really doesn't matter though
            char *temp_buff = (char *)realloc(buff, buff_size);
            if(temp_buff) buff = temp_buff; */
            cursor = buff + line_length;
        }
        fgets(cursor, buff_size - line_length, stdin);
        line_length = strlen(buff);
        //printf("Line length: %d\n", line_length);
        cursor = buff + line_length; //check \0
        // if buffer is about to overflow realloc
        // printf("%s\n", buff);
        /* if buffer contains \n stop */
        //printf("%c\n", buff[line_length - 1]);
        if(strchr(buff, '\n'))  //might be quicker to check buff[line_length - 1]
            stop = true;
    }
    cursor = NULL;
    buff = (char *)realloc(buff, line_length + 1);
    //should the buffer be allocated to reflect the exact length of the string?
    return(buff);
}

/**
 * STRING MANIPULATION
 */
/**
 * Removes trailing whitespace characters from string s substituting '\0' effectively shortening the string.
 * Original string is modified in place, no operations on memory are performed.
 * @param s: pointer to a string which is shortened;
 * @param len: length of the string
 */
int rtrim(char *s, size_t len){
    int result_len = len;
    for(int i = len - 1; i >=0; ++i){
        //isspace requires integer input, so char is converted to unsigned char to avoid problems with implicit char -> int conversion
        if(isspace((unsigned char)s[i])){
            s[i] = '\0';
            --result_len;
        }
    }
    return result_len;
}

int read_int(char *buff){
    return strtol(buff, NULL, 10);
}

/*
 * Reads n integers into an array from a string.
 * @param n: number of integers to be read from buffer
 * @param buff: space separated integers
 * @param data: array[int]
 * @returns number of read integers or 0 if unsuccessful
 */
int read_n_ints(int n, char* buff, int *data){
    int cnt = 0;
    char *tok = strtok(buff, " ");
    do {
        data[cnt] = strtol(tok, NULL, 10);
        tok = strtok(NULL, " ");
        ++cnt;
    } while(tok != NULL);
    return cnt;
}

void print_matrix(int rows, int cols, int **arr){
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j)
            //TODO alignement
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

//TODO function which recognizes type and calls appropriate print fuction for an array

/**
 * Prints array of strings to stdout.
 * @param a: array of strings
 * @param n: # of elements in a
 */
void print_str_array(char **arr, int n){
    for(int i = 0; i < n; ++i)
        printf("%s\n", arr[i]);
}

void print_array(int n, int *arr){
    for(int i = 0; i < n; ++i){
        //TODO alignement
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*
 * Searches for the smallest element in an array of integers (O(n))
 * @param arr pointer to the beginning
 * @param n number of elements in the array
 * @returns the index of the first min element
 */
int min_array(int *arr, int n){
    int min_index = 0;
    int min_int = INT_MAX;
    for(int i = 0; i < n; ++i){
        if(arr[i] < min_int){ 
            min_index = i;
            min_int = arr[i];
        }
    }
    return min_index;
}

/*
 * Searches for the largest element in an array of integers (O(n))
 * @param arr pointer to the beginning
 * @param n number of elements in the array
 * @returns the index of the first max element
 */
int max_array(int *arr, int n){
    int max_index = 0;
    int max_int = INT_MIN;
    for(int i = 0; i < n; ++i){
        if(arr[i] > max_int){ 
            max_index = i;
            max_int = arr[i];
        }
    }
    return max_index;
}

/*
 * Generates an array of n integers in the interval [min_val, max_val].
 */
int *generate_array(int n, int min_val, int max_val){
    int *arr = (int *)malloc(n * sizeof(int));
    
    srand(time(NULL));
    srand(rand());
    //srand(2);    

    for(int i = 0; i < n; ++i)
        arr[i] = rand() % (max_val - min_val + 1) + min_val;
    return arr;
}

int index_of(int *elem, int n, int *arr){
    int index = elem - arr;
    if(index < n) return index;
    return -1;
}

/**
 * @param a: sorted array of integers
 * @int n: number of elements in a
 * @param no: pointer to an integer which will contain the number of elements in the result
 * @return pointer to an integer array containing distinct integers from a
 */
int *select_distinct_ints(int *a, int n, int *no){
    int *result = (int *)malloc(n * sizeof(int));
    result[0] = a[0];
    *no = 0;
    for(int i = 0; i < n; ++i){
        if(result[*no] != a[i]){
            ++(*no);
            result[*no] = a[i];
        }
    }
    result = realloc(result, (*no + 1) * sizeof(int));
    ++(*no);
    return result;
}

/**
 * Performs binary search of a predecessor (arg min of larger elements) of e in an ordered array of distinct integers.
 * @param a: an array of distinct integers sorted in descending order
 * @param n: # of elements in a
 * @param e: element of which a predecessor is searched
 * @returns an index of the predecessor
 */
int bin_search_pred(int *a, int n, int e){
    int start = 0;
    int end = n - 1;
    int mid;
    while(start <= end){
        mid = start + (end - start)/2;
        if(a[mid] < e){
            //go left
            end = mid - 1;
        } else if(a[mid] > e){
            //go right
            start = mid + 1;
        } else return mid - 1;
    }
    // no elements on the left
    if(mid - start == 0) return mid - 1;
    // no elements on the right
    else return mid;
}
