# include <stdio.h>

void intersection(int map[100][100], int result[4]){
	int x, y; 
	result[0] = result[1] = result[2] = result[3] = 0;
	for(y = 0; y < 100; y++){
		for(x = 0; x < 100; x++){
			if (map[x][y] == 1){
				int count = 0;
				if(map[x-1][y] == 1 && x > 0) count++;
				if(map[x+1][y] == 1 && x < 99) count++;
				if(map[x][y-1] == 1 && y > 0) count++;
				if(map[x][y+1] == 1 && y < 99) count++;
				if(count == 4) result[0]++; 
				else if(count == 3) result[1]++;
				else if(count == 1) result[3]++;
				else if(count == 2 && ((map[x-1][y] == 1 && map[x][y-1] == 1 && x > 0 && y > 0) || (map[x-1][y] == 1 && x > 0 && y < 99 && map[x][y+1] == 1) || (map[x+1][y] == 1 && x < 99 && map[x][y-1] == 1 && y > 0) || (map[x+1][y] == 1 && x < 99 && map[x][y+1] == 1 && y < 99))) result[2]++;
			}
		}
	}
	return;
}

int main(){
	int x, y;
	int map[110][110], result[4];
	for(y = 1; y <= 100; y++){
		for(x = 1; x <= 100; x++){
			scanf("%d", &map[x][y]);
		}
	}
	intersection(map, result);
	for(x = 0; x < 4; x++){
		printf("%d\n", result[x]);
	}
}
