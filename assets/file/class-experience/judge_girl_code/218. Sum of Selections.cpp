# include <stdio.h>

int c(int a, int b){
	int i, ans;
	long long mul_a = 1, mul_b = 1, mul_ab = 1;
	for(i = 1; i <= a; i++) mul_a *= i;
	for(i = 1; i <= b; i++) mul_b *= i;
	for(i = 1; i <= a - b; i++) mul_ab *= i;
	ans = mul_a / mul_b / mul_ab;
	return ans;
}

int main(){
	int j, n, m;
	scanf("%d %d", &n, &m);
	long long x = 0;
	for(j = 0; j <= m; j++){
		x += c(n, j);
	}
	printf("%lld", x);
}
