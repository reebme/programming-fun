/*
 * Ordered binary tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <bt.h>
#include <utils.h>

node *new_node(int num){
    node *nn = (node *)malloc(sizeof(node));
    nn->left = NULL;
    nn->right = NULL;
    nn->data = num;
    return nn;
}

/*
 * Prints data in the tree rooted at root.
 * In-order traversal, recursive. 
 */
void inorder(node *root){
    if(root == NULL) return;
    if(root->left) inorder(root->left);
    printf("%d\n", root->data);
    if(root->right) inorder(root->right);
}

/*
 * Prints data in the tree rooted at root.
 * In-order traversal, recursive.
 * This is LCA -> RMQ (with labels or depth) 
 */
void inorder_with_depth(node *root){
    if(root == NULL) return;
    if(root->left) inorder_with_depth(root->left);
    printf("%d\t at depth %d\n", root->data, root->depth);
    if(root->right) inorder_with_depth(root->right);
}

void print_ptr_to_ctree_array(node **ptr_to_ctree, int n){
    for(int i = 0; i < n; ++i)
        printf("%d ", ptr_to_ctree[i]->data);
    printf("\n");
}

/*
 * Creates a Catesian Tree from an array of integers.
 * Recursive. O(n^2).
 * TODO can be built in O(n)
 */
node *arr_to_cart(int n, int *a){
    //printf("Entering arr_to_cart with array starting at %d having %d elements.\n", *a, n);
    //min element of array a which becomes the new root of the (sub)tree
    int min_idx = min_array(n, a);  //(O(n))
    node *root = new_node(a[min_idx]);
    
    int left_low_idx = index_of(a, n, a);
    int left_up_idx = min_idx - 1;
    int right_low_idx = min_idx + 1;
    int right_up_idx = n - 1;
    
    //nothing left on the left to do
    if(left_low_idx <= left_up_idx)
        root->left = arr_to_cart(left_up_idx - left_low_idx + 1, a + left_low_idx);
    
    if(right_low_idx <= right_up_idx)
        root->right = arr_to_cart(right_up_idx - right_low_idx + 1, a + right_low_idx);

    return root;
}

/*
 * Creates a Catesian Tree (ordered binary) from an array of integers.
 * Remembers information which node corresponds to which entry in the original table (point_to_ctree).
 * Recursive. O(n^2).
 * Each node has it's depth recorded.
 * @returns pointer to the root of the Cartesian Tree
 * @param beg: pointer to the first element of the array of integers to be made into a Cartesian Tree
 * @param a: pointer to the first element of the array of integers to be made into a subtree
 * @param n: number of elements from beg to be made into a subtree
 * @param d: current depth of the Cartesian Tree
 * @param point_to_ctree: array of pointers to nodes of the Cartesian Tree
 */
node *arr_to_cart_with_depth(int *beg, int *a, int n, int d, node **point_to_ctree){
    //printf("Entering arr_to_cart with array starting at %d having %d elements.\n", *a, n);
    //min element of array a which becomes the new root of the (sub)tree
    int min_idx = min_array(n, a);  //(finding min is O(n))
    int orig_idx = a - beg + min_idx;
    node *root = new_node(a[min_idx]);
    root->depth = d;
    point_to_ctree[orig_idx] = root;
    
    int left_low_idx = index_of(a, n, a);
    int left_up_idx = min_idx - 1;
    int right_low_idx = min_idx + 1;
    int right_up_idx = n - 1;
    
    //nothing left on the left to do
    if(left_low_idx <= left_up_idx)
        root->left = arr_to_cart_with_depth(beg, a + left_low_idx, left_up_idx - left_low_idx + 1, d + 1, point_to_ctree);
    
    if(right_low_idx <= right_up_idx)
        root->right = arr_to_cart_with_depth(beg, a + right_low_idx, right_up_idx - right_low_idx + 1, d + 1, point_to_ctree);

    return root;
}

/*
 * Reduction of the tree to an array with depth of vertices recorded (LCA -> +- 1 RMQ).
 * Uses Euler tour (inorder walk with every touched vertex recorded).
 * @param root root of an ordered binary tree
 *              each node has it's depth recorded
 * @param tour is 
 */
void euler_tour_with_depth_rec(node *root, struct array_with_curr *tour){
    printf("%d at depth %d\n", root->data, root->depth);
    tour->arr[tour->idx] = root->depth;
    ++tour->idx;
    if(root->left) euler_tour_with_depth_rec(root->left, tour);
    
    if(root->left && root->right){
        printf("%d at depth %d\n", root->data, root->depth);
        tour->arr[tour->idx] = root->depth;
        ++tour->idx;
    }
    
    if(root->right) euler_tour_with_depth_rec(root->right, tour);
    
    if(root->left || root->right){
        printf("%d at depth %d\n", root->data, root->depth);
        tour->arr[tour->idx] = root->depth;
        ++tour->idx;
    }
}

/*
 * Reduction of the tree to an array with depth of vertices recorded (LCA -> +- 1 RMQ).
 * Uses Euler tour (inorder walk with every touched vertex recorded).
 * @param root root of an ordered binary tree
 *              each node has it's depth recorded
 * @param n = |V| (no of vertices in a tree)
 * @returns an aray of integers representing an euler tour with only depth of vertix recorded
 *          array has a size of (|V| - 1)*2 + 1 which represents twice the number of edges of the tree
 */
int *euler_tour_with_depth(node *root, int n){
    struct array_with_curr tour;
    tour.idx = 0;
    // |V| = |E| + 1
    // Euler tour visits every edge twice
    int edge_no = n - 1;
    tour.arr = (int *)malloc((edge_no * 2 + 1) * sizeof(int));
    
    euler_tour_with_depth_rec(root, &tour);
    
    return tour.arr;
}
