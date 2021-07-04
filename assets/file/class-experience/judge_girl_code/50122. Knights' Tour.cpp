# include <stdio.h>
int map[100][100] = {0}, x_knight[10001] = {0}, y_knight[10001] = {0}, step[10001] = {0}, full[10001] = {0};
int main(){
	int n, m, i, j, k;
	int dx[9] = {1, 2, 2, 1, -1, -2, -2, -1, 0};
	int dy[9] = {-2, -1, 1, 2, 2, 1, -1, -2, 0};
	scanf("%d %d", &n, &m);
	for(i = 1; i <= m; i++){
		scanf("%d %d", &y_knight[i], &x_knight[i]);
		map[x_knight[i]][y_knight[i]] = i * 10000;
	}
	int fin = 0;
	while(fin == 0){
		for(i = 1; i <= m; i++){
			int min = 9, best = 8;
			//printf("i = %d\n", i);
			for(j = 0; j < 8; j++){
				if(x_knight[i] + dx[j] >= 0 && y_knight[i] + dy[j] >= 0 && x_knight[i] + dx[j] < n && y_knight[i] + dy[j] < n && map[x_knight[i] + dx[j]][y_knight[i] + dy[j]] == 0){
					//printf("j = %d\n", j);
					int count = 0;
					for(k = 0; k < 8; k++){
						if(x_knight[i] + dx[j] + dx[k] >= 0 && y_knight[i] + dy[j] + dy[k] >= 0 && x_knight[i] + dx[j] + dx[k] < n && y_knight[i] + dy[j] + dy[k] < n && map[x_knight[i] + dx[j] + dx[k]][y_knight[i] + dy[j] + dy[k]] == 0){
							//printf("k = %d\n", k);
							count++;
						}
					}
					if(count < min) {
						min = count;
						best = j;
						//printf("min = %d  best = %d\n", min, best);
					}
				}
			}
			x_knight[i] = x_knight[i] + dx[best];
			y_knight[i] = y_knight[i] + dy[best];
			if(best != 8) step[i]++;
			else if(best == 8) full[i] = 1;
			map[x_knight[i]][y_knight[i]] = i * 10000 + step[i];
		
		/*int s, r;	
		for(r = 0; r < n; r++){
			for(s = 0; s < n; s++){
				printf("%d", map[s][r]);
				if(j != n - 1) printf(" ");
			}
			printf("\n");
		}*/
		
		}
		fin = 1;
		for(j = 1; j <= m; j++){
			if(full[j] == 0){
				fin = 0;
				break;
			}
		}
	}
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%d", map[j][i]);
			if(j != n - 1) printf(" ");
		}
		printf("\n");
	}
	
	
} 
