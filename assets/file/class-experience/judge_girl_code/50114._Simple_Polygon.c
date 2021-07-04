#include <stdio.h>
int main(){
	int ans1 = 0, ans2 = 0, ax, ay, bx, by, cx, cy, dx, dy;
	scanf("%d %d %d %d %d %d %d %d", &ax, &ay, &bx, &by, &cx, &cy, &dx, &dy);
	ans1 = (cx - ax) * (cy - ay) - (cx - bx) * (by - ay) - (dx - ax) * (cy - dy);
	ans2 = ((cx - ax) + (cy - ay)) * 2;
	printf("%d\n%d\n", ans2, ans1);
}