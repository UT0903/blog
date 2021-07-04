#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    struct node *next;
}Node;
Node *merge(Node *list[], int K){
	Node *head;
	Node *now;
#ifdef ZIGZAG
	head = list[0];
	printf("%d\n", head->data);
	int cnt = 0;
	while(1){
		for(int i = 0; i < K; i++){
			if(list[i] != NULL){
				cnt = 0;
				now = list[i];
				now = now->next;
				list[i] = list[i]->next;
			}
			else{
				cnt++;
				if(cnt == K) return head;
			}
		}
		for(int i = K - 1; i >= 0; i--){
			if(list[i] != NULL){
				cnt = 0;
				now->next = list[i];
				now = now->next;
				list[i] = list[i]->next;
			}
			else{
				cnt++;
				if(cnt == K) return head;
			}
		}
	}
#endif
#ifdef TOPDOWN
	head = list[0];
	now = head;
	int cnt = 0;
	while(1){
		for(int i = 0; i < K; i++){
			if(list[i] != NULL){
				cnt = 0;
				now->next = list[i];
				now = now->next;
				list[i] = list[i]->next;
			}
			else{
				cnt++;
				if(cnt == K) return head;
			}
		}
	}
#endif
#ifdef BOTTOMUP
	head = list[K-1];
	now = head;
	int cnt = 0;
	while(1){
		for(int i = K-1; i >= 0; i--){
			if(list[i] != NULL){
				cnt = 0;
				now->next = list[i];
				now = now->next;
				list[i] = list[i]->next;
			}
			else{
				cnt++;
				if(cnt == K) return head;
			}
		}
	}
#endif

}
int main () {
        int K;
        scanf("%d", &K);
        Node *list[K];
        for (int i = 0; i < K; i++) {
                int N;
                scanf("%d", &N);
                if (N == 0) {
                        list[i] = NULL;
                        continue;
                }
                list[i] = (Node *)malloc(sizeof(Node));
                scanf("%d", &(list[i]->data));
                list[i]->next = NULL;
                Node *previous = list[i];
                for (int j = 1; j < N; j++) {
                        previous->next = (Node *)malloc(sizeof(Node));
                        scanf("%d", &(previous->next->data));
                        previous->next->next = NULL;
                        previous = previous->next;
                }
        }
        Node *result = merge(list, K);
        while (result) {
                printf("%d", result->data);
                result = result->next;
                printf("%c", result ? ' ' : '\n');
        };
        return 0;
}