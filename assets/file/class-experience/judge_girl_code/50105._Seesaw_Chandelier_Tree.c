#include <stdio.h>
#include "construct.h"
//#ifndef CONSTRUCT
//#define CONSTRUCT
typedef struct Node{
    int value;
    struct Node *left, *right;
} Node;
 
Node *ConstructTree(int T[], int N){
    int left = 0
    while(left <= right)
}
//#endif

#define MAXN 16384
 
int T[MAXN];
 
void PrintTree( Node *root ){
    if (root == NULL)
        return;
 
    printf("%d\n", root->value);
    PrintTree(root->left);
    PrintTree(root->right);
    return;
}
 
int main(){
    int N;
    scanf("%d", &N);
    for (int i=0; i<N; i++)
        scanf("%d", &T[i]);
 
    Node *tree = ConstructTree( T, N );
 
    PrintTree( tree );
    return 0;
}