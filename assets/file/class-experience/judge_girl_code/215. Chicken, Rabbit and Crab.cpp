# include <stdio.h>
int x = 0, y = 0, z = 0, s, f, t;
int main(){
	scanf("%d %d %d", &s, &f, &t);
	x = -2*t - f/2 + 4*s;
	y = f/2 - 4*s + 3*t ;
	z = s - t;
	if (x < 0 || y < 0 || z < 0 || f % 2 != 0) printf("0");
	else printf("%d\n%d\n%d", x, y, z);
}
