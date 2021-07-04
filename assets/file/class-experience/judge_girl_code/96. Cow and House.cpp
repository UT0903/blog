# include <stdio.h>

int main(){
	double a, b, c, area = 0;
	scanf("%lf %lf %lf", &a, &b, &c);
	area = c * c * 3;
	if(c > b){
		area += (c - b) * (c - b);
	}
	if(c > a){
		area += (c - a) * (c - a);
	}
	area = area * 3.1415926 / 4;
	printf("%f", area);
} 
