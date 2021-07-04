#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//#include "node.h"
struct node {
    struct node *left;
    struct node *right;
    int data;
};
int print[1001];
int count;
void add_data(int data, int count){
    print[count] = data;
    return;
}
void erase_data(int count){
    print[count] = 0;
    return;
}
void print_data(int count){
    for(int i = 0; i < count; i++){
        printf("%d%s", print[i], (i == count - 1)? "\n":" ");
    }
}
void print_all_paths(struct node *root){
    if(root == NULL) return;
    //printf("OK\n");
    add_data(root->data, count);
    count++;
    //printf("count1 = %d\n", count);
    if(root->left == NULL && root->right == NULL){
        print_data(count);
        count--;
        //printf("count2 = %d\n", count);
        erase_data(count);
        
        return;
    }
    print_all_paths(root->left);
    print_all_paths(root->right);
    count--;
    //printf("count3 = %d\n", count);
    erase_data(count);
    return;
}
 
struct node *insert_bs_tree(struct node *root, int data)
{
    struct node *current;
    if (root == NULL)
    {
        current = (struct node *)malloc(sizeof(struct node));
        assert(current != NULL);
        current->data = data;
        current->left = NULL;
        current->right = NULL;
        return current;
    }
 
    if (data < root->data)
        root->left = insert_bs_tree(root->left, data);
    else
        root->right = insert_bs_tree(root->right, data);
    return root;
}
 
int main(void)
{
    int n;
    struct node *root = NULL;
    //printf("OK1\n");
    while (scanf("%d", &n) != EOF)
        root = insert_bs_tree(root, n);
 
    print_all_paths(root);
}