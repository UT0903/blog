#include<stdio.h>
//#include"placement.h"
 
void place(int buckets[1024],int N,int balls[16384],int M,int method,int result[16384]){
	int i, j;
	if(method == 0){
		for(i = 0; i < M; i++){
			for(j = 0; j < N; j++){
				if(buckets[j] >= balls[i]){
					buckets[j] -= balls[i];
					result[i] = j;
					break;
				}
				else {
					result[i] = -1;
				}
			}
		}
	}
	else if(method == 1){
		int best, best_bucket;
		for(i = 0; i < M; i++){
			best = 10000000;
			best_bucket = -1;
			for(j = 0; j < N; j++){
				if(buckets[j] >= balls[i] && buckets[j] < best){
					best = buckets[j];
					best_bucket = j;
				}
			}
			if(best == 10000000){
				result[i] = -1;
			}
			else{
				buckets[best_bucket] = buckets[best_bucket] - balls[i];
				result[i] = best_bucket;
			}
		}
		
	}
	else if(method == 2){
		int worst, worst_bucket;
		for(i = 0; i < M; i++){
			worst = -1;
			worst_bucket = -1;
			for(j = 0; j < N; j++){
				if(buckets[j] >= balls[i] && buckets[j] >= worst){
					worst = buckets[j];
					worst_bucket = j;
				}
			}
			if(worst == -1){
				result[i] = -1;
			}
			else{
				buckets[worst_bucket] = buckets[worst_bucket] - balls[i];
				result[i] = worst_bucket;
			}
		}
	}
	
}
 
int main(){
    int N,M,method;
    scanf("%d%d%d",&N,&M,&method);
    int buckets[N];
    for(int i=0;i<N;i++)
        scanf("%d",&buckets[i]);
    int balls[M];
    for(int i=0;i<M;i++)
        scanf("%d",&balls[i]);
    int result[M];
    place(buckets,N,balls,M,method,result);
    for(int i=0;i<M;i++)
        printf("%d%s",result[i],i==M-1?"":" ");
    return 0;
}
