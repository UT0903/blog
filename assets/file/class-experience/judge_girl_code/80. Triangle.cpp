# include <stdio.h>
# include <stdlib.h>
# include <math.h>

int main()
{
	int n, i;
	scanf("%d", &n); 
	for (i = 0; i < n; i++){
		int x1, y1, x2, y2, x3, y3 ;
		int a, b, c;
		scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
		a = pow(x1-x2, 2) + pow(y1-y2, 2);
		b = pow(x1-x3, 2) + pow(y1-y3, 2);
		c = pow(x3-x2, 2) + pow(y3-y2, 2);
		int space;
		if (b > c){
			space = b;
			b = c;
			c = space;
		}
		if (a > c){
			space = a;
			a = c;
			c = space;
		}
		if (a > b){
			space = a;
			a = b;
			b = space;
		}
	
	//	printf("%d %d %d\n", a, b, c);
		if ((a == b) || (a == c) || (b == c)) printf("isosceles\n");
		else {
			if( a + b > c) printf("acute\n");
			else if( a + b < c) printf("obtuse\n");
			else if ( a + b == c) printf("right\n");
		}
	}
 } 
