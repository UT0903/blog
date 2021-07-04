# include <stdio.h>

int lcm(int x, int y){
	if(x < y){
		int temp;
		temp = x;
		x = y;
		y = temp;
	}
	int x0, y0;
	x0 = x;
	y0 = y;
	int l;
	while(y0 != 0){
	l = x0 % y0;
	x0 = y0;
	y0 = l;
	}
	int z;
	z = x * y / x0;
	return z;
	
}


int a, b, z;
int main(){
	scanf("%d", &a);
	while(scanf("%d", &b) != EOF){
		z = lcm(a, b);
		a = z;
	}
	printf("%d", a);
}
