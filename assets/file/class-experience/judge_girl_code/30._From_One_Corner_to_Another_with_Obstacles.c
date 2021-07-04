#include <stdio.h>
int r,c;
int map[12][12];
int dx[2] = {0, 1};
int dy[2] = {1, 0};
int count = 0;
void walk(int x, int y){
	if(x == c || y == r) return;
	if(map[x][y] == 0) return;
	if(x == c - 1 && y == r - 1){
		count++;
		return;
	}
	for(int i = 0; i < 2; i++){
		walk(x + dx[i], y + dy[i]);
	}
	return;
}

int main(){
	scanf("%d%d", &r, &c);
	for(int i = r - 1; i >= 0; i--){
		for(int j = 0; j < c; j++){
			scanf("%d", &map[j][i]);
		}
	}
	//printf("OK\n");
	walk(0, 0);
	printf("%d\n", count);

}