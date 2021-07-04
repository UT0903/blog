# include <stdio.h>

int main(){
	int n, a[1001], b[1001], i, j = 0, m = 0;
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		int k;
		scanf("%d", &k);
		if (k % 2 == 1) {
			a[j] = k;
			j++;
		}
		else if (k % 2 == 0) {
			b[m] = k;
			m++;
		}
	}
	for (i = 0; i < j-1; i++){
		printf("%d ",a[i]);
	}
	printf("%d\n",a[j-1]);
	
	for (i = 0; i < m-1; i++){
		printf("%d ",b[i]);
	}
	printf("%d",b[m-1]);
}
