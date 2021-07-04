#include <stdio.h>
#include "card.h"
 
void shuffle(int *deck[]){
	int i = 0, j;
	int *temp1[10000] = {0}, *temp2[10000] = {0};
	while(deck[i] != NULL){
		i++;
	}
	for(j = 0; j < ((i % 2 == 0)? (i / 2) : (i / 2 + 1)); j++){
		temp1[j] = deck[j];
	}
	int k = 0;
	for(; deck[j] != NULL; j++){
		temp2[k] = deck[j];
		k++;
	}
	k = 0;
	int l = 0;
	for(j = 0; j < i; j++){
		deck[j] = temp1[k];
		k++;
		j++;
		deck[j] = temp2[l];
		l++;
	}
	
}


void print(int *deck[]){
	int i;
	for(i = 0; deck[i] != NULL; i++){
		printf("%d%s", *deck[i], (deck[i] == NULL)?"" : " ");
	}
}


int main()
{
  int card[10000];
  int *deck[10000];
  int index = 0;
 
  while (scanf("%d", &(card[index])) != EOF) {
    deck[index] = &(card[index]);
    index++;
  }
  deck[index] = NULL;
  shuffle(deck);
  print(deck);  
  return 0;
}
