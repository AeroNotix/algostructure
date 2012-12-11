#include<stdlib.h>
#include<stdio.h>

struct node {
    int val;
    struct node *right;
    struct node * left;
};
typedef struct node node;

void insert(node **tree, node *item) {
    if(*tree == NULL) {
        *tree = item;
        return;
    }
    if(item->val < (*tree)->val)
        insert(&(*tree)->left, item);
    if(item->val > (*tree)->val)
        insert(&(*tree)->right, item);
}

void walk(node **tree) {
    if (*tree == NULL)
        return;
    walk(&(*tree)->left);
    printf("%d\n", (*tree)->val);
    walk(&(*tree)->right);
}

void main() {
    node *curr;
    node *root;
    int i;

    root = NULL;
    
    for(i=1;i<=10;i++) {
        curr = (node*) malloc(sizeof(node));
        curr->left = curr->right = NULL;
        curr->val = rand() % 100;
        insert(&root, curr);
    }
    walk(&root);
}
