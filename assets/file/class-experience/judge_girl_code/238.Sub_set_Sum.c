#include <stdio.h>
int n, data[16], count;
void try(int cmp, int sum, int start){
	//printf("sum = %d\n", sum);
	if(cmp == sum){
		count++;
		//printf("1\n");
		return;
	}
	if(sum > cmp){
		//printf("2\n");
		return;
	}
	if(sum < cmp){
		//printf("3\n");
		for(int i = start; i < n; i++){
			try(cmp, sum + data[i], i + 1);
		}
		return;
	}
	return;
}
int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &data[i]);
	}
	int cmp;
	while(scanf("%d", &cmp) != EOF){
		count = 0;
		try(cmp, 0, 0);
		printf("%d\n", count);
	}
}
