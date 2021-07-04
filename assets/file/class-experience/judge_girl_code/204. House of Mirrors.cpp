# include <stdio.h>
int a[110][110]={0};
int main(){
	int w, d, i, j;
	scanf("%d %d", &w, &d);
	for(i = d; i > 0; i--){
		for(j = 1; j <= w; j++)
		scanf("%d", &a[j][i]);
	}
	int k = 0;
	for(i = 1; i <= w; i++){
		a[i][0] = k;
		k++;
	}
	for(i = 1; i <= d; i++){
		a[w+1][i] = k;
		k++;
	}
	for(i = w; i >= 1; i--){
		a[i][d+1] = k;
		k++;
	}
	for(i = d; i >= 1; i--){
		a[0][i] = k;
		k++;
	}
	/*for(i = d+1; i >= 0; i--){
		for(j = 0; j <= w+1; j++)
		printf("%3d", a[j][i]);
		printf("\n");
	}*/
	int x , y, rx, ry;
	for(x = 1; x <= w; x++){
		int dir = 1; y = 0;
		rx = x; ry = y;
		while(rx <= w && ry <= d){
			if(dir % 2 == 0){
				rx = rx + 1;
			}
			else if (dir % 2 == 1){
				ry = ry + 1;
			}
			if (a[rx][ry] % 2 == 1){
				dir = dir + 1;
				
			}
			else if(a[rx][ry] % 2 == 0){
				dir = dir;
			}
		}
		//printf("1 %d %d\n", rx, ry);
		printf("%d\n", a[rx][ry]);
	}
	for(y = 1; y <= d; y++){
		int dir = 1; x = w+1;
		rx = x; ry = y;
		while(rx >= 1 && ry >= 1){
			if(dir % 2 == 0){
				ry = ry - 1;
			}
			else if (dir % 2 == 1){
				rx = rx - 1;
			}
			if (a[rx][ry] % 2 == 1){
				dir = dir + 1;
				
			}
			else if(a[rx][ry] % 2 == 0){
				dir = dir;
			}
		}
		//printf("2 %d %d\n", rx, ry);
		printf("%d\n", a[rx][ry]);
	}
	for(x = w; x >= 1; x--){
		int dir = 1; y = d+1;
		rx = x; ry = y;
		while(rx >= 1 && ry >= 1){
			if(dir % 2 == 0){
				rx = rx - 1;
			}
			else if (dir % 2 == 1){
				ry = ry - 1;
			}
			if (a[rx][ry] % 2 == 1){
				dir = dir + 1;
				
			}
			else if(a[rx][ry] % 2 == 0){
				dir = dir;
			}
		}
		//printf("3 %d %d\n", rx, ry);
		printf("%d\n", a[rx][ry]);
	}
	for(y = d; y >= 1; y--){
		int dir = 1; x = 0;
		rx = x; ry = y;
		while(rx <= w && ry <= d){
			if(dir % 2 == 0){
				ry = ry + 1;
			}
			else if (dir % 2 == 1){
				rx = rx + 1;
			}
			if (a[rx][ry] % 2 == 1){
				dir = dir + 1;
				
			}
			else if(a[rx][ry] % 2 == 0){
				dir = dir;
			}
		}
		//printf("4 %d %d\n", rx, ry);
		printf("%d\n", a[rx][ry]);
	}
} 
