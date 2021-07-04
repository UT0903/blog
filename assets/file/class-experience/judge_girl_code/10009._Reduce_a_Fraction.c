#include <stdio.h>
int reduce(int a, int b){
	int k = a % b;
	if(k == 0) return b; 
	return reduce(b, k);
}

int main(){
	int a, b;
	while(scanf("%d%d", &a, &b) != EOF){
		int k = reduce(a, b);
		printf("%d / %d\n", a / k, b / k);
	}
}