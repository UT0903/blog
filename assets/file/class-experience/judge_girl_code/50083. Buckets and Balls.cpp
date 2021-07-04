# include <stdio.h>
int n, m, r;
int main(){
	scanf("%d %d %d", &n, &m, &r);
	int k;
	if ( r == 0){
		while (scanf("%d", &k) != EOF){
			if (k <= n) n = n - k;
			else if (k <= m) m = m - k;
			printf("%d %d\n", n, m);
		}
	}
	if ( r == 1){
		while (scanf("%d", &k) != EOF){
			if (k <= n && k <= m){
				if (n <= m) n = n - k;
				else m = m - k;
			}
			else if (k <= n && k > m) n = n - k;
			else if (k > n && k <= m) m = m - k;
			printf("%d %d\n", n, m);
		}
	}
} 
