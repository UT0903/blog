# include <stdio.h>

int main(){ 
	int n, m, i, j, topi, topj;
	scanf("%d %d", &n, &m);
	int a[n][m];
	for (i = 0 ; i < n ; i++){
		for (j = 0 ; j < m ; j++){
			scanf("%d", &a[i][j]);
		}
	}
	
	for (i = 0 ; i < n ; i++){
		int best = 0;
		int sec_best;
		for (j = 0 ; j < m-1 ; j++){
			if(a[i][j+1] >= a[i][best] ) {
				best = j+1;
			}
		}
		if(a[i][1] < a[i][0] && 0 != best) sec_best = 0;
		else sec_best = 1;
		for (j = 0 ; j < m-1 ; j++){
			if(a[i][j+1] >= a[i][sec_best] && (j+1) != best) sec_best = j+1;
		}
		printf("%d %d\n",best+1, sec_best+1);
	}
	int best_i = 0; int best_j = 0;
	for (i = 0 ; i < n ; i++){
		for (j = 0 ; j < m ; j++){
			if(a[i][j] >= a[best_i][best_j] ) {
			best_i = i; best_j = j;			
			}
		}
	}
	printf("%d %d",best_i+1, best_j+1);
}
