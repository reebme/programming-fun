/*
 * Ordered binary tree.
 */

/*
 * Each node label is an integer.
 */
typedef struct node node;
struct node{
    node *left;
    node *right;
    int data;
    //augumentation
    union {
        int height;     
        int depth;
    };
    int idx;
};

struct array_with_curr{
    int *arr;
    int idx;
};

node *new_node(int num);
void print_ptr_to_ctree_array(node **ptr_to_ctree, int n);
void inorder(node *root);
void inorder_with_depth(node *root);
node *arr_to_cart_with_depth(int *a, int *beg, int n, int d, node **point_to_ctree);
node *arr_to_cart(int n, int *a);
int *euler_tour_with_depth(node *root, int n);
void euler_tour_with_depth_rec(node *root, struct array_with_curr *tour);
