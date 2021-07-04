# include <stdio.h>
# include <limits.h> 
int best = 0;
int evaluate_f(int *iptr[], int n, int *index){
	int i, max = INT_MIN, num;
	for(i = 0; i < n; i++){
		num = 4 * (*iptr[i]) - 6 * (*(iptr[i] + 1));
	//	printf("%d\n", num);
		if (num > max){ 
		max = num;
		best = i;
		}
	}
	index = &best;
	return max;
}



#include <stdio.h>
//#include "evaluate_f.h"
 
int main(){
  int a[] = { 9, 7 };
  int b[] = { 3, 2 };
  int c[] = { 3, 2 };
  int d[] = { 9, 7 };
  int *iptr[] = { a, b, c, d };
  int max, index;
  max = evaluate_f(iptr, 4, &index);
  printf("%d %d\n", max, index);
}
