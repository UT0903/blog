#include <stdio.h>
#include <stdlib.h>

void travel(int map[1024][1024], int N, int M, int A_r, int A_c, int B_r, int B_c, int directionA[], int directionB[]){
	int **check = (int**)malloc(1024*sizeof(int*));
    for(int i = 0 ; i < 1024 ; i++) check[i] = (int*)malloc(1024*sizeof(int));
	int A_fin = 0, B_fin = 0, i = 0, j = 0;
	while(A_fin == 0 || B_fin == 0){
		int A_max = -1, A_move = -1, A_r_site = 0, A_c_site = 0, B_move = -1, B_r_site = 0, B_c_site = 0, B_min = 1000000;
		if(A_c == B_c && A_r == B_r){
			A_fin = 1;
			B_fin = 1;
			directionA[i] = -1;
			directionB[j] = -1;
		}
		check[A_r][A_c] = 1;
		check[B_r][B_c] = 1;
		
		if(A_fin == 0){
			if(map[A_r + 1][A_c] > A_max && A_r + 1 < N && map[A_r + 1][A_c] > map[A_r][A_c]){
				A_max = map[A_r +1][A_c];
				A_move = 2;
				A_r_site = A_r + 1;
				A_c_site = A_c;
			//	printf("A2 ");
			}
			if(map[A_r][A_c + 1] > A_max && A_c + 1 < M && map[A_r][A_c + 1] > map[A_r][A_c]){
				A_max = map[A_r][A_c + 1];
				A_move = 0;
				A_r_site = A_r;
				A_c_site = A_c + 1;
			//	printf("A0 ");
			}
			if(map[A_r][A_c - 1] > A_max && A_c > 0 && map[A_r][A_c - 1] > map[A_r][A_c]){
				A_max = map[A_r][A_c - 1];
				A_move = 1;
				A_r_site = A_r;
				A_c_site = A_c - 1;
			//	printf("A1 ");
			}
			if(map[A_r - 1][A_c] > A_max && A_r > 0 && map[A_r - 1][A_c] > map[A_r][A_c]){
				A_max = map[A_r - 1][A_c];
				A_move = 3;
				A_r_site = A_r - 1;
				A_c_site = A_c;
			//	printf("A3 ");
			}
			if(map[A_r + 1][A_c + 1] > A_max && A_r + 1 < N && map[A_r + 1][A_c + 1] > map[A_r][A_c] && A_c + 1 < M){
				A_max = map[A_r + 1][A_c + 1];
				A_move = 4;
				A_r_site = A_r + 1;
				A_c_site = A_c + 1;
			//	printf("A4 ");
			}
			if(map[A_r - 1][A_c - 1] > A_max && A_r > 0 && A_c > 0 && map[A_r - 1][A_c - 1] > map[A_r][A_c]){
				A_max = map[A_r - 1][A_c - 1];
				A_move = 5;
				A_r_site = A_r - 1;
				A_c_site = A_c - 1;
			//	printf("A5 ");
			}
			if(map[A_r - 1][A_c + 1] > A_max && A_r > 0 && A_c + 1 < M && map[A_r - 1][A_c + 1] > map[A_r][A_c]){
				A_max = map[A_r - 1][A_c + 1];
				A_move = 6;
				A_r_site = A_r - 1;
				A_c_site = A_c + 1;
			//	printf("A6 ");
			}
			if(map[A_r + 1][A_c - 1] > A_max && A_r + 1 < N && A_c > 0 && map[A_r + 1][A_c - 1] > map[A_r][A_c]){
				A_max = map[A_r + 1][A_c - 1];
				A_move = 7;
				A_r_site = A_r + 1;
				A_c_site = A_c - 1;
			//	printf("A7 ");
			}
			if(A_move == -1) {
				A_fin = 1;
				directionA[i] = -1;
			}
			
			if(A_move != -1){
				directionA[i] = A_move;
				i++;
				A_r = A_r_site;
				A_c = A_c_site;
			}
			if(check[A_r_site][A_c_site] == 1){
					directionA[i] = -1;
					A_fin = 1;
			}
		}
		if(B_fin == 0){
			if(map[B_r + 1][B_c] < B_min && B_r + 1 < N && map[B_r + 1][B_c] < map[B_r][B_c]){
				B_min = map[B_r +1][B_c];
				B_move = 2;
				B_r_site = B_r + 1;
				B_c_site = B_c;
			//	printf("B2 ");
			}
			if(map[B_r][B_c + 1] < B_min && B_c + 1 < M && map[B_r][B_c + 1] < map[B_r][B_c]){
				B_min = map[B_r][B_c + 1];
				B_move = 0;
				B_r_site = B_r;
				B_c_site = B_c + 1;
			//	printf("B0 ");
			}
			if(map[B_r][B_c - 1] < B_min && B_c > 0 && map[B_r][B_c - 1] < map[B_r][B_c]){
				B_min = map[B_r][B_c - 1];
				B_move = 1;
				B_r_site = B_r;
				B_c_site = B_c - 1;
			//	printf("B1 ");
			}
			if(map[B_r - 1][B_c] < B_min && B_r > 0 && map[B_r - 1][B_c] < map[B_r][B_c]){
				B_min = map[B_r - 1][B_c];
				B_move = 3;
				B_r_site = B_r - 1;
				B_c_site = B_c;
			//	printf("B3 ");
			}
			if(map[B_r + 1][B_c + 1] < B_min && B_r + 1 < N && map[B_r + 1][B_c + 1] < map[B_r][B_c] && B_c + 1 < M){
				B_min = map[B_r + 1][B_c + 1];
				B_move = 4;
				B_r_site = B_r + 1;
				B_c_site = B_c + 1;
			//	printf("B4 ");
			}
			if(map[B_r - 1][B_c - 1] < B_min && B_r > 0 && B_c > 0 && map[B_r - 1][B_c - 1] < map[B_r][B_c]){
				B_min = map[B_r - 1][B_c - 1];
				B_move = 5;
				B_r_site = B_r - 1;
				B_c_site = B_c - 1;
			//	printf("B5 ");
			}
			if(map[B_r - 1][B_c + 1] < B_min && B_r > 0 && B_c + 1 < M && map[B_r - 1][B_c + 1] < map[B_r][B_c]){
				B_min = map[B_r - 1][B_c + 1];
				B_move = 6;
				B_r_site = B_r - 1;
				B_c_site = B_c + 1;
			//	printf("B6 ");
			}
			if(map[B_r + 1][B_c - 1] < B_min && B_r + 1 < N && B_c > 0 && map[B_r + 1][B_c - 1] < map[B_r][B_c]){
				B_min = map[B_r + 1][B_c - 1];
				B_move = 7;
				B_r_site = B_r + 1;
				B_c_site = B_c - 1;
			//	printf("B7 ");
			}
			if(B_move == -1) {
				B_fin = 1;
				directionB[j] = -1;
			}
			
			if(B_move != -1){
				directionB[j] = B_move;
				j++;
				B_r = B_r_site;
				B_c = B_c_site;
			}
			if(check[B_r_site][B_c_site] == 1){
					directionB[j] = -1;
					B_fin = 1;
			}
			
		}
		
	}
		
	
	
}
 
int main() {
    int N, M;
    int map[1024][1024];
    int A_r, A_c, B_r, B_c;
    int directionA[1024], directionB[1024];
 
    scanf("%d%d", &N, &M);
 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &map[i][j]);
        }
    }
 
    scanf("%d%d%d%d", &A_r, &A_c, &B_r, &B_c);
 
    travel(map, N, M, A_r, A_c, B_r, B_c, directionA, directionB);
 
    int i = 0;
    while (directionA[i] != -1) {
        printf("%d ", directionA[i]);
        i++;
    }
    printf("-1\n");
    i = 0;
    while (directionB[i] != -1) {
        printf("%d ", directionB[i]);
        i++;
    }
    printf("-1\n");
 
    return 0;
}

