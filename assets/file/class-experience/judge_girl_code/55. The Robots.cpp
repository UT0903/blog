#include <stdio.h>

int main(){
	int M,N,X1,Y1,E1,N1,F1,X2,Y2,E2,N2,F2, time = 0, dir1 = 1, dir2 = 0, i, count1 = 0, count2 = 0, count = 0;
	scanf("%d %d %d %d %d %d %d %d %d %d %d %d", &M, &N, &X1, &Y1, &E1, &N1, &F1, &X2, &Y2, &E2, &N2, &F2);
	
	while(F1 != 0 || F2 != 0){
		if(F1 > 0){
			if(dir1 % 2 == 0){
				X1++;
				count1++;
				if(count1 == E1){
					count1 = 0;
					dir1++;
				}
			}
			else if (dir1 % 2 == 1){
				Y1++;
				count1++;
				if(count1 == N1){
					count1 = 0;
					dir1++;
				}
			}
			X1 = X1 % M;
			Y1 = Y1 % N;
			F1--;
		}
		if(F2 > 0){
			if(dir2 % 2 == 0){
				X2++;
				count2++;
				if(count2 == E2){
					count2 = 0;
					dir2++;
				}
			}
			else if (dir2 % 2 == 1){
				Y2++;
				count2++;
				if(count2 == N2){
					count2 = 0;
					dir2++;
				}
			}
			X2 = X2 % M;
			Y2 = Y2 % N;
			F2--;
		}
		time++;
		if(X1 % M == X2 % M && Y1 % N == Y2 % N){
			printf("robots explode at time %d", time);
			count = 1;
			break;
		}
	}
	if(count == 0) printf("robots will not explode");
}
