# include <stdio.h>
int map[600][600] = {0};
int main(){
	int n, m, l, w, i, o, o_x, o_y, x, y;
	scanf("%d %d %d %d", &n, &m, &l, &w);
	int tank_x = 0, tank_y = 0;
	scanf("%d", &o);
	for(i = 0; i < o; i++){
		scanf("%d %d", &o_x, &o_y);
		map[o_x][o_y] = 2;
	}
	for(x = tank_x; x < tank_x + w; x++){
		for(y = tank_y; y < tank_y+l; y++){
			map[x][y] = 1;
		}
	}
	
	int order, ok;
	while(scanf("%d", &order) != EOF){
		if(order == 0){
			for(y = 0; y < n; y++){
				for( x = 0; x < m; x++){
					printf("%d", map[x][y]);
				}
				printf("\n");
			}
		}
		else if(order == 1){
			ok = 0;
			for(y = tank_y; y < tank_y + l; y++){
				x = tank_x + w;
				ok += map[x][y];
			}
			if(ok <= 2 && tank_x + w < m){
				for(y = tank_y; y < tank_y + l; y++){
					x = tank_x;
					map[x][y] = 0;
				}
				tank_x++;
				for(x = tank_x; x < tank_x + w; x++){
					for(y = tank_y; y < tank_y+l; y++){
						map[x][y] = 1;
					}
				}
			}
		}
		else if(order == 4){
			ok = 0;
			for(x = tank_x; x < tank_x + w; x++){
				y = tank_y - 1;
				ok += map[x][y];
			}
			if(ok <= 2 && tank_y > 0){
				for(x = tank_x; x < tank_x + w; x++){
					y = tank_y + l - 1;
					map[x][y] = 0;
				}
				tank_y--;
				for(x = tank_x; x < tank_x + w; x++){
					for(y = tank_y; y < tank_y + l; y++){
						map[x][y] = 1;
					}
				}
			}
		}
		else if(order == 3){
			ok = 0;
			for(y = tank_y; y < tank_y + l; y++){
				x = tank_x - 1;
				ok += map[x][y];
			}
			if(ok <= 2 && tank_x > 0){
				for(y = tank_y; y < tank_y + l; y++){
					x = tank_x + w - 1;
					map[x][y] = 0;
				}
				tank_x--;
				for(x = tank_x; x < tank_x + w; x++){
					for(y = tank_y; y < tank_y+l; y++){
						map[x][y] = 1;
					}
				}
			}
		}
		else if(order == 2){
			ok = 0;
			for(x = tank_x; x < tank_x + w; x++){
				y = tank_y + l;
				ok += map[x][y];
			}
			if(ok <= 2 && tank_y + l < n){
				for(x = tank_x; x < tank_x + w; x++){
					y = tank_y;
					map[x][y] = 0;
				}
				tank_y++;
				for(x = tank_x; x < tank_x + w; x++){
					for(y = tank_y; y < tank_y + l; y++){
						map[x][y] = 1;
					}
				}
			}
		}
		else if(order == 5){
			ok = 0;
			for(x = tank_x + 1; x < tank_x + w; x++){
				y = tank_y + l;
				ok += map[x][y];
			}
			for(y = tank_y + 1; y <= tank_y + l; y++){
				x = tank_x + w;
				ok += map[x][y];
			}
			if(ok <= 2 && tank_y + l < n && tank_x + w < m){
				for(x = tank_x; x < tank_x + w; x++){
					y = tank_y;
					map[x][y] = 0;
				}
				for(y = tank_y; y < tank_y + l; y++){
					x = tank_x;
					map[x][y] = 0;
				}
				tank_x++; tank_y++;
				for(x = tank_x; x < tank_x + w; x++){
					for(y = tank_y; y < tank_y + l; y++){
						map[x][y] = 1;
					}
				}
			}
		}
	}
}
