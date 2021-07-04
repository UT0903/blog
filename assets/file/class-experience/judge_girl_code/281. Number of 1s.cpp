# include <stdio.h>
int n, i;
int main(){
	while(~scanf("%d", &n)){
		int count = 0;
		for(i = 0; (n >> i) != 0; i++){
			if(n >> i & 1){
				count++;
			}
		}
		printf("%d\n", count);
	}
}
