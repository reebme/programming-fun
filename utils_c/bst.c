#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <bst.h>

node* insert_node(int num, node *root){
    if(root == NULL){
        root = new_node(num);
        return root;
    }
    node *curr = root;
    if(curr->data < num){
        if(curr->right == NULL){
            curr->right = new_node(num);
            return curr->right;
        }
        else insert_node(num, curr->right);
    } else {
        if(curr->left == NULL){
            curr->left = new_node(num);
            return curr->left;
        }
        else insert_node(num, curr->left);
    }
}

node *insert_node_with_height(int num, node *root){
    if(root == NULL){
        root = new_node(num);
        return root;
    }
    node *curr = root;
    if(curr->data < num){
        if(curr->right == NULL){
            curr->right = new_node(num);
            //update height after child addition
            update_height(curr);
            return curr->right;
        }
        else insert_node_with_height(num, curr->right);
    } else {
        if(curr->left == NULL){
            curr->left = new_node(num);
            //update height after child addition
            update_height(curr);
            return curr->left;
        }
        else insert_node_with_height(num, curr->left);
    }
    //propagating height update up the recursion stack
    update_height(curr);
}

void update_height(node *node){
    if(node->height == 0 || ((!node->left && node->right) || (!node->right && node->left))) ++node->height;
    else{
        if(node->left && node->right)
            node->height = (node->left->height > node->right->height) ? (node->left->height + 1) : (node->right->height + 1);
    }
}

/*
 * @param root is the root of an ordered binary tree
 * @returns height of the ordered binary tree rooted at root
 * Uses recursion.
 */
int get_height(node *root){
    if(root == NULL) return 0;
    if(root->left == NULL && root->right == NULL) return 0;
    int left_height = get_height(root->left);
    int right_height = get_height(root->right);
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

node *new_node_with_height(int num){
    node *nn = (node *)malloc(sizeof(node)); //new node
    nn -> height = 0;
    nn -> data = num;
    nn -> left = NULL;
    nn -> right = NULL;
    return nn;
}
