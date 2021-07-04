# include <stdio.h>
int a[1001][1001];
int max = 0;
int count;
int main(){
	int n, x, y;
	scanf("%d", &n);
	for(y = 0; y < n; y++){
		for(x = 0; x < n; x++){
			scanf("%d", &a[x][y]);
		}
	}
	

	for(y = 0; y < n; y++){
		count = 0;
		for(x = 0; x < n; x++){
			if(a[x][y] == 1) {
				count++;
				if (count > max) max = count;
			//	printf("1 = %d\n", max);
			}
			else count = 0;
		}
		
	}
	for(x = 0; x < n; x++){
		count = 0;
		for(y = 0; y < n; y++){
			if(a[x][y] == 1) {
				count++;
				if (count > max) max = count;
			//	printf("2 = %d\n", max);
			}
			else count = 0;
		}
		
	}
	for(y = 0; y < n; y++){
		count = 0;
		for(x = 0; x < n - y; x++){
			if(a[x+y][x] == 1) {
				count++;
				if (count > max) max = count;
			//	printf("3 = %d\n", max);
			}
			else count = 0;
		}
	}
	
	for(y = 0; y < n; y++){
		count = 0;
		for(x = 0; x < n - y; x++){
			if(a[x][x+y] == 1) {
				count++;
				if (count > max) max = count;
			//	printf("4 = %d\n", max);
			}
			else count = 0;
		}
	}
	printf("%d", max);
}
