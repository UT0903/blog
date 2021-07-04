#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
typedef struct input{
	int num;
	int level;
}Input;

Input a[100000];

int n;

struct treenode{
	int data;
	struct treenode *left;
	struct treenode *right;
};
typedef struct treenode Treenode;
char path[10000];
Treenode *Find_the_path(Treenode *root, int data){
	if(data == root->data){
		return(root);
	}
	else if(data < root->data){
		strcat(path, "l");
		root->left = Find_the_path(root->left, data);
		return(root);
	}
	else if(data > root->data){
		strcat(path, "r");
		root->right = Find_the_path(root->right, data);
		return(root);
	}
}
Treenode *Insert_bs_tree(Treenode *root, int data){
	Treenode *current;
	if(root == NULL){
		current = (Treenode*)malloc(sizeof(Treenode));
		assert(current != NULL);
		current->data = data;
		current->left = NULL;
		current->right = NULL;
		return(current);
	}
	if(data < root->data){
		root->left = Insert_bs_tree(root->left, data);
	}
	else{
		root->right = Insert_bs_tree(root->right, data);
	}
	return(root);
}
int Compare(char a[1000], char b[1000]){
	int i = 0;
	while(a[i] == b[i]){
		i++;
	}
	int w = strlen(a);
	int x = strlen(b);
	//printf("strlen(a) = %d\n", w);
	//printf("strlen(b) = %d\n", x);
	//printf("i = %d\n", i);
	return (strlen(a) + strlen(b) - (i * 2));
}
int d;
int main(){
	Treenode *root = NULL;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d %d", &a[i].num, &a[i].level);
	}
	int check = 0;
	int current_level = 1;
	while(check < n){
		for(int i = 0; i < n; i++){
			if(current_level == a[i].level){
				root = Insert_bs_tree(root, a[i].num);
				check++;
			}
		}
		current_level++;
	}
	scanf("%d", &d);
	for(int i = 0; i < d; i++){
		char path2[10000], path1[10000];
		int p, q;
		scanf("%d %d", &p, &q);
		memset(path, '\0', 10000);
		root = Find_the_path(root, p);
		strcpy(path1, path);
		memset(path, '\0', 10000);
		root = Find_the_path(root, q);
		strcpy(path2, path);
		int distance = Compare(path1, path2);
		printf("%d\n", distance);
	}
}