# include <stdio.h>
int l, w, a[101][101], x, y;
int main(){
	scanf("%d %d", &l, &w);
	for(y = 0; y < l; y++){
		for(x = 0; x < w; x++){
			scanf("%d", &a[x][y]);
		}
	}
	for(x = 0; x < w; x++){
		int sum = 0;
		for(y = 0; y < l; y++){
			sum += a[x][y];
		}
		sum = sum / l;
		printf("%d\n", sum);
	}
}
