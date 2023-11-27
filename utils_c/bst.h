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
};

node *new_node_with_height(int num);
node *insert_node(int data, node *root);
node *insert_node_with_height(int data, node *root);
void update_height(node *node);
int get_height(node *root);
