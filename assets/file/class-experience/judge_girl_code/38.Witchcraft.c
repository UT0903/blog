#include <stdio.h>
long long int sum,lim_a,lim_b,lim_c, numa, numb, numc;
long long int witch(long long int coda, long long int a, long long int b, long long int c){
	//printf("coda = %lld a = %lld b = %lld c = %lld\n", coda, a, b, c);
	if(coda > sum) return 0;
	if(a == -1 || b == -1 || c == -1) return 0;
	if(coda == sum) return 1;
	if(witch(coda + numa, a - 1, b, c)){
		return 1;
	}
	if(witch(coda + numb, a, b - 1, c)){
		return 1;
	}
	if(witch(coda + numc, a, b, c - 1)){
		return 1;
	}
	return 0;
}
int main(){
	int n;
	scanf("%d", &n);

	while(n--){
		scanf("%lld%lld%lld%lld%lld%lld%lld", &sum, &lim_a, &lim_b, &lim_c, &numa, &numb, &numc);
		if(witch(0, lim_a,lim_b,lim_c)) printf("yes\n");
		else printf("no\n");
	}
}
