# include <stdio.h>
 
struct situ {
    long long x, y;
};
 
int main()
{
    struct situ a, b;
    long long x, y, dx1, dx2, dy1, dy2, t, i;
    scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld", &x, &y, &a.x, &a.y, &b.x, &b.y, &dx1, &dy1, &dx2, &dy2, &t);
 
    for (i=0; i<t; i++){
        a.x += dx1; a.y += dy1;
        b.x += dx2; b.y += dy2;
        if (a.x == b.x && a.y == b.y){
            if (dx1 == (-dx2)){
                dx1 = -dx1;
                dx2 = -dx2;
            }
            if (dy1 == (-dy2)){
                dy1 = -dy1;
                dy2 = -dy2;
            }
        }
        if (a.x == 1 || a.x == x){
            dx1 = -dx1;
        }
        if (a.y == 1 || a.y == y){
            dy1 = -dy1;
        }
        if (b.x == 1 || b.x == x){
            dx2 = -dx2;
        }
		if (b.y == 1 || b.y == y){
            dy2 = -dy2;
        }
        printf("%lld ", a.x);
    	printf("%lld\n", a.y);
    	printf("%lld ", b.x);
    	printf("%lld\n\n", b.y);
    }
    printf("%lld\n", a.x);
    printf("%lld\n", a.y);
    printf("%lld\n", b.x);
    printf("%lld\n", b.y);
}
