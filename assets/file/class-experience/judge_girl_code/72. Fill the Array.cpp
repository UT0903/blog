#include <stdio.h>

//#include "fill_array.h"
/*int find_left(int arr[], int i, int n){
	while(arr[i] == 0 && i >= 0){
		i--;
	}
	return arr[i];
}

int find_left(int arr[], int i, int n){
	
	while(arr[i] == 0 && i < n){
		i++;
	}
	return arr[i];
}*/


void fill_array(int *ptr[], int n){
	int i, min_best, max_best;
	int *min = ptr[0], *max = ptr[0];
	for(i = 0; i < n; i++){
		*ptr[i] = i;
		if(ptr[i] < min) {
			min = ptr[i];
			min_best = i;
		}
		if(ptr[i] > max) {
			max = ptr[i];
			max_best = i;
		}
	}
	int *k, *use1, *use2, *l;
	for(k = min + 1; k <= max; k++){
		int open = 0;
		use1 = k-1;
		if(*k == 0){
			open = 1;
			while(*k == 0) k++;
		}
		use2 = k;
		if(open == 1){
			for(l = use1 + 1; l < use2; l++){
				*l = *use1 + *use2;
			}
		}
	}
}

	
	
	//ptr[i] = ptr[i] + 1;
	/*
	for(i = 0; i < n ; i++){
		printf("%d ", *k);
		k++;
	}
	printf("\n");*/

	
	

	/*i = 0;
	int l, r;
	while(*ptr[i] == 0){
		l = find_left(ptr, i, n);
		r = find_right(ptr, i, n);
		if(l != 0 && r != 0){
			*ptr[i] = l + r;
		}
		i++;
	}*/



int main() {
    int arr[100] = {};
    int *ptr[100];
    int n = 6, m = 0;
    int A[100] = {0, 5, 6, 9, 3, 12};
    for (int i = 0; i < n; i++) {
        ptr[i] = &arr[A[i]];
        if (A[i] > m)    m = A[i];
    }
    fill_array(ptr, n);
    for (int i = 0; i <= m; i++)
        printf("%d%c", arr[i], " \n"[i==m]);
    return 0;
}
