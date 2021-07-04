#include <stdio.h>
#include <math.h>

int gcd(int i ,int j){
	while (i != 0){
		int r = j % i;
		j = i;
		i = r;
	}
	return j;
} 
 
int main(){
	int a, b, c, d, e, f, g, h, i, j, x, y, z;
	scanf("%d %d %d %d %d %d %d", &a ,&b, &c, &d, &e, &f, &g);
	if (a < 0) b = -b;
	if (e < 0) f = -f;
	
	if (d == 0){
		b = a * c + b;
		f = e * g + f;
		j = c * g;
		i = b * g + c * f;
		h = i / j;
		if (i != 0){
		i = i % j;
		}
		if (i < 0) i = -i;
		if (i == 0) j = 1; 
		else x = i; y = j;
			z = gcd(i, j);
			i = x / z;
			j = y / z;
		
		
		
	}
	if (d == 1){
		b = a * c + b;
		f = e * g + f;
		j = c * g;
		i = b * g - c * f;
		h = i / j;
		if (i != 0){
		i = i % j;
		}
		if (i < 0) i = -i;
		if (i == 0) j = 1; 
		else x = i; y = j;
			z = gcd(i, j);
			i = x / z;
			j = y / z;
		}
	if (d == 2)	{
		b = a * c + b;
		f = e * g + f;
		j = c * g;
		i = b * f;
		h = i / j;
		if (i != 0){
		i = i % j;
		}
		if (i < 0) i = -i;
		if (i == 0) j = 1; 
		else x = i; y = j;
			z = gcd(i, j);
			i = x / z;
			j = y / z;
	}
	if (d == 3)	{
		b = a * c + b;
		f = e * g + f;
		j = c * f;
		i = b * g;
		h = i / j;
		if (i != 0){
		i = i % j;
		}
		if (i < 0) i = -i;
		if (j < 0) j = -j;
		if (i == 0) j = 1; 
		else x = i; y = j;
			z = gcd(i, j);
			i = x / z;
			j = y / z;
	}
	printf("%d\n%d\n%d", h, i, j);
}
