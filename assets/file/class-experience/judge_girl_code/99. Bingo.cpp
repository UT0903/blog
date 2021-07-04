# include <stdio.h>

long long n, m, i, bingo[11][260][260], x, y, bin[11] = {0};
int x_[11][70000], y_[11][70000], rcnt[11][260], ccnt[11][260];
char name[11][70];
int main (){
	
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++){
		scanf("%s", name[i]);
		for(y = 1; y <= m; y++){
			for(x = 1; x <= m; x++){
				scanf("%d", &bingo[i][x][y]);
				x_[i][bingo[i][x][y]] = x;
				y_[i][bingo[i][x][y]] = y;
				 
			}
		}
	}
	
	int r, ok;
	while(scanf("%d", &r) != EOF){
		for(i = 0; i < n; i++){
			bingo[i][x_[i][r]][y_[i][r]] = 0;
			rcnt[i][x_[i][r]]++;
			ccnt[i][y_[i][r]]++;
			
			
			
			for(y = 1; y <= m; y++){
				if(ccnt[i][y] == m) {
					bin[i] = 1;
					break;
				}
			}
			
			
			for(x = 1; x <= m; x++){
				if(rcnt[i][x] == m) {
					bin[i] = 1;
					break;
				}
			}
			
			ok = 0;
			for(x = 1; x <= m; x++){
				ok += bingo[i][x][x];
			}
			if (ok == 0) {
				bin[i] = 1;
				//printf("c");
			}
			
			ok = 0;
			for(x = 1; x <= m; x++){
				ok += bingo[i][x][m+1-x];
			}
			if (ok == 0) {
				bin[i] = 1;
				//printf("d");
			}
			
		}
		
		/*for(i = 0; i < n; i++){
			for(y = 1; y <= m; y++){
				for(x = 1; x <= m; x++){
					printf("%5d", bingo[i][x][y]);
				}
				printf("\n");
			}
			printf("\n");
		}*/
		
	
		for(i = 0; i < n; i++){
			if(bin[i] == 1){
				printf("%d", r);
				break;
			}
		}
		int fin = 0;
		for(i = 0; i < n; i++){
			if(bin[i] == 1){
				fin = 1;
				printf(" %s", name[i]);
			}
		}
		if(fin == 1) break;
		
	}
	
}
