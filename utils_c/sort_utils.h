typedef struct big_int big_int;
struct big_int{
    char *num;  //number represented as a string
    size_t len; //no of digits in num
};

void counting_sort(big_int *a, int n, int pos);
void radix_sort(big_int *a, int n, size_t max_int_len);
