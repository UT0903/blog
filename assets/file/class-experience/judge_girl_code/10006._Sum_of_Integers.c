#include <stdio.h>
int sum = 0, n;
int main(){
	while(scanf("%d", &n) != EOF){
		sum += n;
	}
	printf("%d\n", sum);
}