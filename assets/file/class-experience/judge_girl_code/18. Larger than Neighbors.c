# include <stdio.h>
int a[110][110] = {0}, l, w, y, x;
int main(){
	scanf("%d %d", &l, &w);
	for(y = 1; y <= l; y++){
		for(x = 1; x <= w; x++) scanf("%d", &a[x][y]);
	}
	for(y = 1; y <= l; y++){
		for(x = 1; x <= w; x++){
			if(a[x][y] > a[x-1][y] && a[x][y] > a[x+1][y] && a[x][y] > a[x][y-1] && a[x][y] > a[x][y+1]) printf("%d\n", a[x][y]);
		}
	}
}
