#include <stdio.h>
int a[110][110] = {0};
int main(){
	int x, y, inter = 0, tjunc = 0, turn = 0, dead = 0, n;
	scanf("%d", &n);
	for(y = 1; y <= n; y++){
		for(x = 1; x <= n; x++){
			scanf("%d", &a[x][y]);
		}
	}
	for(y = 0; y <= n; y++){
		for(x = 0; x <= n; x++){
			if (a[x][y] == 1){
				int count = 0;
				if(a[x-1][y] == 1 && x > 0) count++;
				if(a[x+1][y] == 1 && x < n) count++;
				if(a[x][y-1] == 1 && y > 0) count++;
				if(a[x][y+1] == 1 && y < n) count++;
				if(count == 4) inter++; 
				else if(count == 3) tjunc++;
				else if(count == 1) dead++;
				else if(count == 2 && a[x-1][y] != a[x+1][y] && a[x][y-1] != a[x][y+1]) turn++;
			}
		}
	}
	printf("%d\n%d\n%d\n%d\n", inter, tjunc, turn, dead);
} 
