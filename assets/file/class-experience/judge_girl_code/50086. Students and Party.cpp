# include <stdio.h>

int a[32769][257] = {0}, check[32769] = {0};
int main(){
	int n, e, i, x, y, j;
	scanf("%d %d", &n, &e);
	for(i = 0; i < e; i++){
		scanf("%d %d", &x, &y);
		x = x + 1;
		y = y + 1;
		j = 0;
		while(a[x][j] != 0) j++;
		a[x][j] = y;
		j = 0;
		while(a[y][j] != 0) j++;
		a[y][j] = x;
	}
	
	/*for(i = 1; i <= n; i++){
		for(j = 0; j < 256; j++){
			if(a[i][j] != 0) printf("%d ", a[i][j]);
		}
		printf("\n");
	}*/
	int id;
	while(scanf("%d", &id) != EOF){
		id = id + 1;
		check[id] = 1;
		j = 0;
		while(a[id][j] != 0) {
		check[a[id][j]] = 1;
		j++;
		}
	}
	for(i = 1; i <= n; i++){
		if(check[i] == 0) printf("%d\n", i - 1);
	}
}
