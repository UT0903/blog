# include <stdio.h>
int a[2050];
int main(){
	int n, i;
	scanf("%d", &n);
	for(i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	int fin = 0, k = 0, temp, x;
	while(fin == 0){
		int sum;
		for(x = 0; x < n && fin == 0; x++){
			sum = 0;
			for(i = 0; i < n && fin == 0; i++){
				sum += a[i] * (i - x); 
			}
			if(sum == 0) fin = 1;
		}
		if(fin == 0){
			temp = a[k];
			a[k] = a[n-1-k];
			a[n-1-k] = temp;
			k++;
		}
	}
	for(i = 0; i < x - 1; i++){
		printf("%d ", a[i]);
	}
	printf("v");
	for(i = x; i < n; i++){
		printf(" %d", a[i]);
	}
	
	
} 
