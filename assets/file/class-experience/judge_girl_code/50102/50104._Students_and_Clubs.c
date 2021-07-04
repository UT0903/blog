#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct club {
  char club_name[64];
  char leader_name[64];
  int code;
  struct club *left;
  struct club *right;
};
typedef struct club Club;

struct student {
  char member_name[64];
  struct student *left;
  struct student *right;
};
typedef struct student Student;

/*void print_bs_tree(TreeNode *root)
{
  if (root == NULL)
    return;
  print_bs_tree(root->left);
  printf("data = %d\n", root->data);
  print_bs_tree(root->right);
}*/
Student *insert_member(Student *root, char *member_name)
{
  Student *current;
  if (root == NULL) {
    current = (Student*)malloc(sizeof(Student));
    assert(current != NULL);
    strcpy(current->member_name, member_name);
    current->left = NULL;
    current->right = NULL;
    return(current);
  }
  if (strcmp(member_name < root->member_name) < 0) 
    root->left = insert_bs_tree(root->left, member_name);
  else 
    root->right =insert_bs_tree(root->right, member_name);
  return(root);
}

Club *insert_club(Club *root, char *leader_name, char *club_name)
{
  Club *current;
  if (root == NULL) {
    current = (Club*)malloc(sizeof(Club));
    assert(current != NULL);
    strcpy(current->club_name, club_name);
    strcpy(current->leader_name, leader_name);
    current->code = code;
    current->left = NULL;
    current->right = NULL;
    return(current);
  }
  if (strcmp(club_name < root->club_name) < 0) 
    root->left = insert_bs_tree(root->left, leader_name, club_name, code);
  else 
    root->right =insert_bs_tree(root->right, leader_name, club_name, code);
  return(root);
}
int find_code(char *club_name){
  while(strcmp() != ){
    
  }
}

int main(){
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; i++){
    int order; 
    scanf("%d", order);
    char member_name[64], club_name[64];
    scanf("%s %s", member_name, club_name);
    Club *root_club = NULL;
    Student *root_member[5000];
    int code = 0;
    if(order == 0){
      root_club = insert_club(root_club, member_name, club_name, code);
      root_member[code] = insert_club(root_member[code], member_name);
      code++;
    }
    else{
      int x = find_code(club_name);
      root_member[x] = insert_club(root_member[x], member_name);
    }
  }
  int m;
  scanf("%d", &m);
  for(int i = 0; i < m; i++){

  }
}