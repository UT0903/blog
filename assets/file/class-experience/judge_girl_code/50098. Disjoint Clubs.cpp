# include <stdio.h>
# include <string.h>
# include <stdlib.h>

int Find(unsigned long long int group[], int N, int K, int start, int ans[]){
	if(K == 0){ 
		return 1;
	}
	else{
		for(int i = start; i < N; i++){
			//printf("i = %d\n", i);
			if((group[i] & group[start]) == 0) {
				ans[K] = i;
				return Find(group, N, K - 1, i, ans);
			}
		}
		ans[K] = 0;
		return 0;
	}
}


unsigned long long int group[101], cmp[64];
int group_num[101];
int ans[101];

int main(){
	unsigned long long int pow = 1;
	for(int k = 0; k < 64; k++){
		cmp[k] = pow;
		pow *= 2;
		//printf("cmp[%d] = %llu\n", k, cmp[k]);
	}
	int N, K, num;
	scanf("%d %d", &N, &K);
	for(int i = 0; i < N; i++){
		scanf("%d", &num);
		for(int j = 0; j < num; j++){
			int digit;
			scanf("%d", &digit);
			//printf("digit = %d\n", digit);
			group[i] = (group[i] | cmp[digit]);
			//printf("group[%d] = %llu\n", i, group[i]);
		}
	}
	for(int i = 0; i < N; i++){
		if(Find(group, N, K - 1, i, ans)){
			ans[K] = i;
			break;
		}
	}
	for(int i = K; i >= 1; i--){
		printf("%d\n", ans[i]);
	}
	
}
