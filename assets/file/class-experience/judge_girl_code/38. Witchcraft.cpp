# include <stdio.h>
int check(int sum, int limit_a, int limit_b, int limit_c, int a, int b, int c, int i, int j, int k){
	if (i*a + j*b + k*c > sum) return 0;
	if(sum == i*a + j*b + k*c) return 1;
	if(k + 1 <= limit_c && i <= limit_a && j <= limit_b) {
		if (check(sum, limit_a, limit_b, limit_c, a, b, c, i, j, k + 1)){
		// printf("ans i = %d j = %d k = %d\n", i, j, k);
			return 1;
		}
	}
	if(i <= limit_a && j + 1 <= limit_b && k <= limit_c){
		if (check(sum, limit_a, limit_b, limit_c, a, b, c, i, j + 1, k)){
		// printf("ans i = %d j = %d k = %d\n", i, j, k);
			return 1;
		}
	} 
	if(i + 1 <= limit_a && k <= limit_c && j <= limit_b) {
		if (check(sum, limit_a, limit_b, limit_c, a, b, c, i + 1, j, k)){
		// printf("ans i = %d j = %d k = %d\n", i, j, k);
			return 1;
		}
	}
	// printf("i = %d j = %d k = %d\n", i, j, k);
	return 0;
}

int main(){
	int n, sum, limit_a, limit_b, limit_c, a, b, c;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d %d %d %d %d %d %d", &sum, &limit_a, &limit_b, &limit_c, &a, &b, &c);
		if(check(sum, limit_a, limit_b, limit_c, a, b, c, 0, 0, 0)) printf("yes\n");
		else printf("no\n");
	}
}
