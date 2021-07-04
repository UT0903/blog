# include <stdio.h>
int n, a[100000], m, b[200001], i;
int main(){
	scanf("%d", &n);
	for(i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	scanf("%d", &m);
	int k;
	for(i = 0; i < n; i++){
		k = a[i] % m;
		b[k]++;
	}
	for(i = 0; i < m; i++) printf("%d\n", b[i]);
}
