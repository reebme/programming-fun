#include <stdio.h>

char* get_line_by_char();
char* get_line(FILE *in_file);
int read_int(char *);
int read_n_ints(int, char *, int *);
void print_matrix(int, int, int **);
void print_array(int, int *);
int min_array(int *arr, int n);
int max_array(int *arr, int n);
int *generate_array(int n, int min_val, int max_val);
int index_of(int *elem, int n, int *arr);
int *select_distinct_ints(int *, int, int *);
int bin_search_pred(int *a, int n, int e);
void print_str_array(char **arr, int n);
size_t rtrim(char *s);
