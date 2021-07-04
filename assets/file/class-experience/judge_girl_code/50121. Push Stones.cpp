#include <stdio.h>
int map[500][500];
int main(){
	int M, N, i, j, move, x, y, fuel, num ;
	scanf("%d %d", &N, &M);
	int dx[5] = {0, 1, 0, -1, 0};
	int dy[5] = {0, 0, 1, 0, -1};
	scanf("%d %d %d", &y, &x, &fuel);
	map[x][y] = fuel;
	scanf("%d", &num);
	int stone_x, stone_y, stone_weight;
	for(i = 0; i < num; i++){
		scanf("%d %d %d", &stone_y, &stone_x, &stone_weight);
		map[stone_x][stone_y] = stone_weight;
	}
	while(scanf("%d", &move) != EOF){
		if(move == 0){
			for(i = 0; i < N; i++){
				for(j = 0; j < M; j++){
					printf("%d", map[j][i]);
					if(j != M - 1) printf(" ");
				}
				printf("\n");
			}
		}
		else if(x + dx[move] < M && x + dx[move] >= 0 && y + dy[move] < N && y + dy[move] >= 0){
			/*printf("before\n");
			for(i = 0; i < N; i++){
				for(j = 0; j < M; j++){
					printf("%d ", map[j][i]);
				}
				printf("\n");
			}*/
			int sum = 0, count;
			for(count = 1; map[x + dx[move] * count][y + dy[move] * count] != 0 && x + dx[move] * count >= 0 && y + dy[move] * count >= 0; count++){
				sum += map[x + dx[move] * count][y + dy[move] * count];
			}
			//printf("sum = %d\n", sum);
			//printf("count = %d\n", count);
			
			if(fuel >= sum && x + dx[move] * count < M && y + dy[move] * count < N && x + dx[move] * count >= 0 && y + dy[move] * count >= 0){
				//printf("in\n");
				fuel = fuel - sum;
				for( ; count > 1; count--){
					map[x + dx[move] * count][y + dy[move] * count] = map[x + dx[move] * (count - 1)][y + dy[move] * (count - 1)];
				}
				map[x + dx[move]][y + dy[move]] = fuel;
				map[x][y] = 0;
				x += dx[move];
				y += dy[move];
			}
			/*printf("After\n");
			for(i = 0; i < N; i++){
				for(j = 0; j < M; j++){
					printf("%d ", map[j][i]);
				}
				printf("\n");
			}*/
			
			/*for(i = 0; i < N; i++){
				for(j = 0; j < M; j++){
					printf("%d ", map[j][i]);
				}
				printf("\n");
			}*/
		}
	}
	
}
