#include <stdio.h>
int n, m, check[1000][1000], q;
int main(){
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 0; i < q; i++){
		int lx, ly, rx, ry, count = 0;;
		scanf("%d%d%d%d", &lx, &ly, &rx, &ry);
		for(int x = lx; x <= rx; x++){
			for(int y = ly; y <= ry; y++){
				if(check[x][y] == 0){
					count++;
				}
			}
		}
		printf("%d", count);
		for(int x = lx; x <= rx; x++){
			for(int y = ly; y <= ry; y++){
				if(check[x][y] == 0){
					printf(" (%d, %d)", x, y);
					check[x][y] = 1;
				}
			}
		}
		printf("\n");
	}

}