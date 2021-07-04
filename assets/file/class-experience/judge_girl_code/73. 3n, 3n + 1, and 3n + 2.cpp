# include <stdio.h>

int main(){
	int n, i, j, ew0 = 0, ew1 = 0, ew2 = 0;
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		scanf("%d", &j);
		if (j % 3 == 0) ew0++;
		else if (j % 3 == 1) ew1++;
		else if (j % 3 == 2) ew2++;
	}
	printf("%d %d %d", ew0, ew1, ew2);
}
