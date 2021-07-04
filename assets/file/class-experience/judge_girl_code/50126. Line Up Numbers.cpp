#include <stdio.h> 
/*void FindSmall_A( int A[], int B[], int i, int j, int *turn, int x, int y, int* a[], int* b[]){
    printf("OK");
	if(A[x] < B[y]){
    	a[i] = &B[y];
    	i++;
    	y++;
    	*turn = 1;
	}
	else{
		a[i] = &A[x];
		i++;
		x++;
	}
}

void FindSmall_B( int A[], int B[], int i, int j, int *turn, int x, int y, int* a[], int* b[]){
    printf("OK2");
	if(A[x] < B[y]){
    	b[j] = &A[x];
    	j++;
    	x++;
    	*turn = 0;
	}
	else{
		b[j] = &B[y];
		j++;
		x++;
	}
}*/


void merge(int A[], int B[], int* a[], int* b[]){
	int i = 0, j = 0, turn, x = 0, y = 0, countA = 1, countB = 1;
	for(i = 0; a[i] != 0; i++) countA++;
	for(i = 0; b[i] != 0; i++) countB++;
	i = 0;
	//printf(" countA = %d, countB = %d\n", countA, countB);
	if(A[0] < B[0]){
		turn = 0;
		x++;
	}
	else{
		turn = 1;
		y++;
	}
	int close = 0, close1 = 0, close2 = 0;
	//printf("x = %d, y = %d, turn = %d\n", x, y, turn);
	int count = 0;
	while(a[i] != NULL && b[j] != NULL){
		
		if(turn == 0){
			//FindSmall_A(A, B, i, j, turn, x, y, a, b);
			if(A[x] > B[y]){
    			a[i] = &B[y];
    		//	printf("1a[%d] = %d ", i, *a[i]);
    			i++;
    			y++;
    			turn = 1;
    		//	printf("turn = %d\n", turn);
			}
			else{
				a[i] = &A[x];
			//	printf("2a[%d] = %d ", i, *a[i]);
				i++;
				x++;
			//	printf("turn = %d\n", turn);
			}
			
			
		}
		else if(turn == 1){
			//FindSmall_B(A, B, i, j, turn, x, y, a, b);
			if(A[x] < B[y]){
    			b[j] = &A[x];
    			//printf("1b[%d] = %d ", j, *b[j]);
    			j++;
    			x++;
    			turn = 0;
    			//printf("turn = %d\n", turn);
			}
			else{
				b[j] = &B[y];
				//printf("2b[%d] = %d ", j, *b[j]);
				j++;
				x++;
				//printf("turn = %d\n", turn);
			}
		}
		
	}
	
	if(a[i] == NULL && close == 0){
		a[i] = 0;
		a[i+1] = NULL;
		close = 1;
		//turn = (turn+1) % 2;
		
	}
	else if(b[j] == NULL && close == 0){
		b[j] = 0;
		b[j+1] = NULL;
		close = 1;
		//turn = (turn+1) % 2;
		
	}
	
	while(a[i] != NULL && b[j] != NULL){
		
		if(turn == 0){
			//FindSmall_A(A, B, i, j, turn, x, y, a, b);
			if(A[x] > B[y]){
    			a[i] = &B[y];
    		//	printf("1a[%d] = %d ", i, *a[i]);
    			i++;
    			y++;
    			turn = 1;
    		//	printf("turn = %d\n", turn);
			}
			else{
				a[i] = &A[x];
			//	printf("2a[%d] = %d ", i, *a[i]);
				i++;
				x++;
			//	printf("turn = %d\n", turn);
			}
			
			
		}
		else if(turn == 1){
			//FindSmall_B(A, B, i, j, turn, x, y, a, b);
			if(A[x] < B[y]){
    			b[j] = &A[x];
    			//printf("1b[%d] = %d ", j, *b[j]);
    			j++;
    			x++;
    			turn = 0;
    			//printf("turn = %d\n", turn);
			}
			else{
				b[j] = &B[y];
				//printf("2b[%d] = %d ", j, *b[j]);
				j++;
				x++;
				//printf("turn = %d\n", turn);
			}
		}
		
	}
	
	
	//printf("i = %d, j = %d\n", i, j);
	if(a[i] != NULL){
		while(a[i] != NULL){
			if(A[x] < B[y] && A[x] != 0){
				a[i] = &A[x];
			//	printf("3a[%d] = %d\n", i, *a[i]);
				i++;
				x++;
			}
			else if(B[y] != 0){
				a[i] = &B[y];
			//	printf("4a[%d] = %d\n", i, *a[i]);
				i++;
				y++;
			}
		}
	}
	
	else if(b[j] != NULL){
		while(b[j] != NULL){
			if(A[x] < B[y] && A[x] != 0){
				b[j] = &A[x];
				//printf("3b[%d] = %d\n", j, *b[j]);
				j++;
				x++;
			}
			else if(B[y] != 0){
				b[j] = &B[y];
				//printf("4b[%d] = %d\n", j, *b[j]);
				j++;
				y++;
			}
		}
	}
	
	for(i = 0; a[i] != 0; i++){
		printf("a[%d] =  %d ", i, *a[i]);
	}
	printf("\n");
	for(i = 0; b[i] != 0; i++){
		printf("b[%d] =  %d", i, *b[i]);
	}
	printf("\n");
	

	
	/*if(a[i] == NULL){
		while(b[j] != NULL){
			
			j++;
		}
	}
	else if(b[j] == NULL){
		while(a[i] != NULL){
			
			i++;
		}
	}*/
	
}


#include <stdio.h>
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
