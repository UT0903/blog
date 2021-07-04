#include <stdio.h>

int main(){
	int x;
	while (scanf("%d", &x) == 1){
		printf("%d ", (x/1000));
		x = x % 1000;
		printf("%d ", (x/500));
		x = x % 500;
		printf("%d ", (x/100));
		x = x % 100;
		printf("%d ", (x/50));
		x = x % 50;
		printf("%d ", (x/10));
		x = x % 10;
		printf("%d ", (x/5));
		x = x % 5;
		printf("%d\n", x);
	}
} 
