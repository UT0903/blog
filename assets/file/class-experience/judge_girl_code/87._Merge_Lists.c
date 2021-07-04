/*
#ifndef _NODE_H
#define _NODE_H
 
struct node {
    int value;
    struct node * next;
};
 
struct node * merge(struct node *, struct node *);
 
#endif
*/
#include <stdio.h>
#include <stdlib.h>
//#include "node.h"
 
#define LEN 1000

struct node {
    int value;
    struct node * next;
};

struct node *merge_sb(struct node *list1, struct node *list2, struct node *head){
	if(list1 == NULL && list2 == NULL) return head;

	if(list2 == NULL){
		head->next = list1;
		//printf("OK1 list1 value = %d\n", list1->value);
		merge_sb(list1->next, list2, head->next);
	}
	else if(list1 == NULL){
		head->next = list2;
		//printf("OK2 list2 value = %d\n", list2->value);
		merge_sb(list1, list2->next, head->next);
	}
	else if(list1->value < list2->value){
		head->next = list1;
		//printf("OK1 list1 value = %d\n", list1->value);
		merge_sb(list1->next, list2, head->next);

	}
	else{
		head->next = list2;
		//printf("OK2 list2 value = %d\n", list2->value);
		merge_sb(list1, list2->next, head->next);
	}
	return head;

}
struct node *merge(struct node *list1, struct node *list2){
	struct node *head = NULL;
	if(list1->value < list2->value){
		//printf("OK1\n");
		head = list1;
		merge_sb(list1->next, list2, head);
	}
	else{
		//printf("OK2\n");
		head = list2;
		merge_sb(list1, list2->next, head);
	}
	return head;
} 

struct node * build(int v[], int n) {
    struct node * head, * ptr;
    int i;
 
    if (!n)
        return 0;
 
    head = (struct node *) malloc(sizeof(struct node));
    ptr = head;
    head -> value = v[0];
    for (i = 1; i < n; i++) {
        ptr -> next = (struct node *) malloc(sizeof(struct node));
        ptr = ptr -> next;
        ptr -> value = v[i];
    }
    ptr -> next = 0;
    return head;
}
 
void print(struct node * ptr) {
    printf("%d", ptr -> value);
    if (ptr -> next) {
        putchar(' ');
        print(ptr -> next);
    }
}
 
int main() {
    int n1, n2;
    int v1[LEN], v2[LEN];
    int i;
    struct node * list1, * list2;
 
    scanf("%d", &n1);
    for (i = 0; i < n1; i++)
        scanf("%d", &v1[i]);
    scanf("%d", &n2);
    for (i = 0; i < n2; i++)
        scanf("%d", &v2[i]);
    list1 = build(v1, n1);
    list2 = build(v2, n2);
 
    print(merge(list1, list2));
    putchar('\n');
    return 0;
}