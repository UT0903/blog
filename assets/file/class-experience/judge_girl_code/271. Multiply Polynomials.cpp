# include <stdio.h>

int main(){
	int a[300], b[300], c[300] = {0}, n, m, i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	scanf("%d", &m);
	for(i = 0; i < m; i++){
		scanf("%d", &b[i]);
	}
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++){
			c[i + j] += a[i] * b[j];
		}
	}
	for(i = 0; i < n+m-2; i++){
		printf("%d ", c[i]);
	}
	printf("%d", c[n+m-2]);
}

