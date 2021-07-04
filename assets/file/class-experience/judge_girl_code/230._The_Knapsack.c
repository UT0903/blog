# include <stdio.h>
# include <limits.h>

int n, W, max = INT_MIN;
int w[1000], v[1000];
void Find(int left, int v_sum, int i){
	//printf("left = %d, v_sum = %d, i = %d\n", left, v_sum, i);
	if(i == n){
		//printf("return\n");
		if(v_sum > max){
			max = v_sum;
		}
		return;
	}
	Find(left, v_sum, i + 1);
	if(left - w[i] < 0){
		//printf("return\n");
		if(v_sum > max){
			max = v_sum;
		}
		return;
	}
	Find(left - w[i], v_sum + v[i], i + 1);
	return;
}

int main(){
	scanf("%d%d", &n, &W);
	for(int i = 0; i < n; i++){
		scanf("%d%d", &w[i], &v[i]);
	}
	Find(W, 0, 0);
	printf("%d\n", max);
}