# include <stdio.h>

int main(){
	int n, i;
	while(~scanf("%d", &n)){
		int count = 0;
		for(i = 0; n != 0; n &= (n >> 1) ){
			count++;
		}
		printf("%d\n", count);
	} 
} 
