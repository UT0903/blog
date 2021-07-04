# include <stdio.h>

int gcd(int x, int y){
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
	return x0;	
}

int value(int m, int a, int b, int c){
	int price;
	if(m != 79 && m != 47 && m != 29 && m != 82 && m != 26 && m != 22) price = -1;
	else if(a <= 0 || b <= 0 || c <= 0) price = -2;
	else{
		int s1, s2, s;
		s1 = gcd(a, b);
		s2 = gcd(c, b);
		s = gcd(s1, s2);
		a = a / s;
		b = b / s;
		c = c / s;
		if(m == 79) price = a * b * c * 30 * s * s * s * s * s * s;
		if(m == 47) price = a * b * c * 10 * s * s * s * s * s * s;
		if(m == 29) price = a * b * c * 4 * s * s * s * s * s * s;
		if(m == 82) price = a * b * c * 5 * s * s * s * s * s * s;
		if(m == 26) price = a * b * c * 3 * s * s * s * s * s * s;
		if(m == 22) price = a * b * c * 9 * s * s * s * s * s * s;
	}
	return price;
}

int main(){
	int ans, m, a, b, c;
	scanf("%d %d %d %d", &m, &a, &b, &c);
	ans = value(m, a, b, c);
	printf("%d", ans);
}
