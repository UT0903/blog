#include <stdio.h>
int main(){
	int a, b, h, c, d, v, ans;
	scanf("%d %d %d %d %d", &a, &b, &h, &c, &d);
	v = a * b * h;
	ans = v / (a * b - c * d);
	printf("%d\n", ans);
}