#include <stdio.h>

void merge(int A[], int B[], int* a[], int* b[]){
	int i = 0, j = 0, now;
	int num_a = 0, num_b = 0;
	while(a[num_a] != NULL){
		num_a++;
	}
	num_a++;
	while(b[num_b] != NULL){
		num_b++;
	}
	num_b++;

	if(A[0] < B[0])
		now = 0;
	else
		now = 1;
	while (i < num_a && j < num_b){
        if(A[i] < B[j]){
        	if(now){
        		j++;	
        	}
        	else{
        		a[i] = &B[j];
        		i++;
        	}
        	now = 0;
        }
        else{
        	if(now){
        		b[j] = &A[i];
        		i++;
        	}
        	else{
				j++;
        	}
        	now = 1;
        }
    }
    if(i == num_a){
    	a[num_a - 1] = &B[j];
        for(; j < num_b; j++){
        	b[j] = &B[j+1];
        }
    }
    else if(j == num_b){
    	b[num_b - 1] = &A[i];
        for(; i < num_a; i++){
			a[i] = &A[i+1];
        }
    }
}

int main()
{
    int A[10], B[10];
    int *a[10], *b[10], *ans_a[10], *ans_b[10];
    int i, N, M;
 
    scanf("%d%d", &N, &M);
    for(i = 0; i < N; i++)
        scanf("%d", &A[i]);
    for(i = 0; i < M; i++)
        scanf("%d", &B[i]);
    for(i = 0; i < N-1; i++)
        a[i] = &A[i+1];
    a[N-1] = NULL;
    for(i = 0; i < M-1; i++)
        b[i] = &B[i+1];
    b[M-1] = NULL;
 
    merge(A, B, a, b);
 
    ans_a[0] = &B[0]; ans_a[1] = &A[2]; ans_a[2] = &B[1]; ans_a[3] = &B[2];
    ans_b[0] = &A[1]; ans_b[1] = &A[3]; ans_b[2] = NULL;
 
    for(i = 0; i < N; i++){
        if(a[i] != ans_a[i])
            printf("a[%d] is Wrong!\n", i);
    }
    for(i = 0; i < M; i++){
        if(b[i] != ans_b[i])
            printf("b[%d] is Wrong!\n", i);
    }
    printf("Finish!\n");
    return 0;
}