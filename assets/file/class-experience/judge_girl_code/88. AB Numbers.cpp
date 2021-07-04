# include <stdio.h>

int main (){
	int x[4], y[4], n, m, i, j;
	scanf("%d %d", &n, &m);
	for (i = 0 ; i < 4; i++){
		x[i] = n % 10;
		y[i] = m % 10;
		n = n / 10;
		m = m / 10;
	}
	//printf("%d %d %d %d %d %d %d %d", x[0], x[1], x[2], x[3], y[0], y[1], y[2], y[3]);
	int a = 0, b = 0;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			if (x[j] == y[i]){
				if (j == i) a++;
				else b++;
			}
	//		printf("%dA%dB\n", a, b);
		}
	}
	printf("%dA%dB", a, b);
}
