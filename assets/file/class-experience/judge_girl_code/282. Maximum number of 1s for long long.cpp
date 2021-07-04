# include <stdio.h>
int i;
long long n;
int main(){
	while(~scanf("%lld", &n)){
		int count = 0;
		for(i = 0; (n >> i) != 0; i++){
			if(n >> i & 1){
				count++;
			}
		}
		printf("%d\n", count);
	}
}
