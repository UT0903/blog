# include <stdio.h>

int main(){
	int n, i, x[4], y[4], j, temp, k; 
	scanf("%d", &n);
	for(i = 0; i < n; i++){
		scanf("%d %d %d %d %d %d %d %d", &x[0], &y[0], &x[1], &y[1], &x[2], &y[2], &x[3], &y[3]);
	for( i = 0; i < 4; i++) {
    	for( j = i; j < 4; j++) {
    		if( x[j] * y[(j+1) % 4] - x[(j+1) % 4] * y[j] < 0 ) {
        		temp = x[j];
        		x[(j + 1) % 4] = x[j];
        		x[j] = temp;
        		
        		temp = y[j];
        		y[(j + 1) % 4] = y[j];
        		y[j] = temp;
            }
        }
    }
    printf("%d %d %d %d %d %d %d %d\n", x[0], y[0], x[1], y[1], x[2], y[2], x[3], y[3]);
    
	}
} 
