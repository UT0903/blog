# include <stdio.h>
int plus(int n, int count){
	//printf("n = %d, count = %d\n", n, count);
	if(n == 0){
		//printf("out %d\n", n);
		return count;
	}
	else{
		
		count += (n * n);
		//printf("count = %d\n", count);
		return plus(n - 1, count);
	}
}

int main(){
	int n, sum;
	scanf("%d", &n);
	int count = 0;
	sum = plus(n, count);
	printf("%d", sum);
} 
