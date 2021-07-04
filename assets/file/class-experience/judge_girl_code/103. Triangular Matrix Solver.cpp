# include <stdio.h>
double a[17][17] = {0}, b[17] = {0}, f[17] = {0};
int main(){
	int x, y, n, i;
	scanf("%d", &n);
	for(y = 0; y < n; y++){
		for(x = 0; x < n; x++){
			scanf("%lf", &a[x][y]);
		}
	}
	for(i = 0; i < n; i++){
		scanf("%lf", &b[i]);
	}
	double up = 0;
	for(x = n - 1; x >= 0; x--){
		up = b[x];
		for(y = n - 1; y >= x; y--){
		 	up = up - a[y][x] * f[y];
		}
		f[x] = up / a[x][x];
	}
	for(i = 0; i < n; i++){
		printf("%f\n", f[i]);
	}
	
}
