# include <stdio.h>
int digit = 0, n, zero = 0, count = 0, fir = 0, sec = 0, even;
int main (){
	while (scanf("%d", &n) != EOF){
		even = 0;
		digit++;
		if (n % 2 == 0) even = 1;
		if (n == 0) zero++ ;
		if (count % 2 == 0){
			fir += n;
			count++;
		}
		else if(count % 2 == 1){
			sec += n;
			count++;
		}
	}
	int ele = 0;
	if ((fir - sec) % 11 == 0) ele = 1;
	printf ("%d\n%d\n%d\n%d\n", digit, even, zero, ele);
}
