# include <stdio.h>

int main(){
	int a, b, max_a = -10001, max_b = -10001, min_a = 10001, min_b = 10001, area;
	while(scanf("%d %d", &a, &b) != EOF){
		if(a > max_a) max_a = a;
		if(b > max_b) max_b = b;
		if(a < min_a) min_a = a;
		if(b < min_b) min_b = b;
	}
	area = (max_a - min_a) * (max_b - min_b);
	printf("%d", area);
}
