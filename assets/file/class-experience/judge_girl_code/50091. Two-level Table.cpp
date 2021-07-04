# include <stdio.h>
int **fir[500], *sec[500];
int ***constructTable(int A[], int B[]){
	int j = 0, i = 0;
	
		int k = 0;
		while(B[i] != 0 || B[i + 1] != 0){
			sec[k] = &B[i];
			while(B[i] != 0) i++;
			i++;
			k++;
		}
		/*for(i = 0; sec[i] != 0; i++){
			printf("%d ", *sec[i]);
		}*/
		k = 0;
		i = 0;
		int l = 0;
		while(A[i] != 0){
			j = 0;
			fir[k] = &sec[l];
			while(j < A[i]){
				j++;
				l++;
			}
			k++;
			i++;
		}
		//printf("OK");
		return &fir[0];
}

#include <stdio.h>
//#include "constructTable.h"
 
int main(){
    int N, M;
    int A[100] = {}, B[500] = {};
    scanf("%d%d", &N, &M);
    for(int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    for(int i = 0; i < M; i++)
        scanf("%d", &B[i]);
 
    int ***ptr;
    ptr = constructTable(A, B);
    for(int i = 0; *(ptr+i) != NULL; i++)
        for(int j = 0; j < A[i]; j++)
            for(int k = 0; *(*(*(ptr+i)+j)+k) != 0; k++)
                printf("%d ", *(*(*(ptr+i)+j)+k));
    return 0;
}
