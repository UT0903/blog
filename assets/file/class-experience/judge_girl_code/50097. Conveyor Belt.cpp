#include<stdio.h>
//#include"transmission.h"
#define MAXSIZE 1048576
int temp[1049000];
long long int tem[1049000];
void transmission(long long int belt[],int N,int T){
	int shift_n = (T - (T % 64)) / 64;
	int shift_t = T % 64;
	//printf("%d, %d\n", shift_n, shift_t);
	for(int i = 0; i < N; i++){
		tem[i] = belt[(i + shift_n) % N];
	}
	for(int i = 0; i < N; i++){
		belt[i] = tem[i];
	}
	
	for(int i = 0; i < shift_t; i++){
		for(int j = 0; j < N; j++){
			if(belt[j] >= 0) temp[j] = 0;
			else temp[j] = 1;
			//printf("temp[%d] = %d\n", j, temp[j]); 
		}
		for(int j = 0; j < N; j++){
			belt[j] = (belt[j] << 1) + temp[(j+1) % N];
			//printf("belt[%d] = %lld\n", j, belt[j]);
		}
	}
}


long long int belt[MAXSIZE];
int main(){
    int N,T;
    scanf("%d%d",&N,&T);
    for(int i=0;i<N;i++)
        scanf("%lld",&belt[i]);
    transmission(belt,N,T);
    for(int i=0;i<N;i++)
        printf("%lld%s",belt[i],i==N-1?"":" ");
    return 0;
}
