# include <stdio.h>
int a[1010][3] = {0}, i, x, n, k;

int main(){
	for(i = 0; i < 1010; i++){
		a[i][2] = 100000;
	}
	scanf("%d %d", &n, &k);
	for(i = 0; i < n; i++){
		scanf("%d", &x);
		a[x % k][0] += x;
		if(x > a[x % k][1]){
			a[x % k][1] = x;
		}
		if(x < a[x % k][2]){
			a[x % k][2] = x;
		}
	}
	for(i = 0; i < k; i++){
		printf("%d %d %d\n", a[i][0], a[i][1], a[i][2]);
	}
	
}
