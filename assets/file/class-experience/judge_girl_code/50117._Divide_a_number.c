#include <stdio.h>
int main(){
	int k, N = 0, input, in = 0;
	scanf("%d", &k);
	while(scanf("%d", &input) != EOF){
		N = (N % k) * 10 + input;
		if(N/k != 0 || in == 1){
			in = 1;
			printf("%d\n", N/k);
		}
	}
	if(in == 0){
		printf("0\n");
	}
}