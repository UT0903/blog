#include <stdio.h>
#include <stdlib.h>

int r, c;
int map[401][401];
int check[401][401];
int lake[400 * 400 / 2 + 1];
int dx[4] = {0, 1, -1, 0};
int dy[4] = {1, 0, 0, -1};
int count;
void Findlake(int x, int y){
	//printf("x = %d, y = %d\n", x, y);
	
	if(x == r || x < 0 || y == c || y < 0){
		return;
	}
		
	if(map[x][y] == 0){
		return;
	} 
	if(check[x][y] == 1){
		return;
	} 
	check[x][y] = 1;
	count++;
	for(int i = 0; i < 4; i++){
		Findlake(x + dx[i], y + dy[i]);
	}
	return;

}
int cmp(const void *a, const void *b){
	return (*(int*)b - *(int*)a);
}

int main(){
	scanf("%d%d", &r, &c);
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			scanf("%d", &map[i][j]);
		}
	}
	int k = 0;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			if(map[i][j] == 1 && check[i][j] == 0){
				Findlake(i, j);
				lake[k] = count;
				k++;
				count = 0;
			}
		}
	}
	qsort(lake, k, sizeof(lake[0]), cmp);
	for(int i = 0; i < k; i++){
		printf("%d\n", lake[i]);
	}
}