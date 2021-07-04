#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct treenode(){
	int data;
	struct treenode *left;
	struct treenode *right;
	struct treenode *root;
};

typedef struct treenode Treenode;
Treenode *Build_bs_tree(Treenode *root, int data){
	
}
char tmp[10];
char input[4001];
int main(){
	scanf("%s", input);
	int n = strlen(input);
	Treenode *root = (Treenode *)malloc(sizeof(Treenode));
	Treenode *tmp;
	root->left = NULL;
	root->right = NULL;
	root->root = NULL;
	Treenode *current_place = root;
	for(int i = 0; i < n; i++){
		if(input[i] == '('){
			Treenode *newplace = (Treenode *)malloc(sizeof(Treenode));
			tmp = current_place;
			current_place = current_place->left;
			current_place->root = tmp;
		}
		else if(input[i] == ','){

		}
		else if(input[i] == ')'){

		}
		else{
			memset(tmp, '\0', 10);
			while(isdigit(input[i])){
				strcat(tmp, input[i]);
				i++;
			}
			int num = atoi(tmp);

		}
	}
	
}