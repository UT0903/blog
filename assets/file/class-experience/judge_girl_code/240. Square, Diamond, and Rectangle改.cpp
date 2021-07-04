# include <stdio.h>
int main (){
	int n, i;
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		int xa, ya, xb, yb, xc, yc, x0, y0 ,temp;
		scanf("%d %d %d %d %d %d %d %d", &x0, &y0, &xa, &ya, &xb, &yb, &xc, &yc);
		xa = xa - x0;
		ya = ya - y0;
		xb = xb - x0;
		yb = yb - y0;
		xc = xc - x0;
		yc = yc - y0;
		if (xa*yb-xb*ya < 0){
			temp = xa;
			xa = xb;
			xb = temp;
		
			temp = ya;
			ya = yb;
			yb = temp;
		}
		if (xb*yc-xc*yb < 0){
			temp = xb;
			xb = xc;
			xc = temp;
			
			temp = yb;
			yb = yc;
			yc = temp;
		}
		if (xa*yb-xb*ya < 0){
			temp = xa;
			xa = xb;
			xb = temp;
			
			temp = ya;
			ya = yb;
			yb = temp;
		}
		//printf("%d %d %d %d %d %d", xa, ya, xb, yb, xc, yc);
		int length = 0, angle = 0;
		if (xa*xa + ya*ya == xc*xc + yc*yc && (xb-xa)*(xb-xa) + (yb-ya)*(yb-ya) == xa*xa + ya*ya && (xb-xc)*(xb-xc) + (yb-yc)*(yb-yc) == xa*xa + ya*ya){
			length = 1;
		}
		if (xa * xc + ya * yc ==0 && (xb - xa) * xa +(yb - ya) * ya == 0 && (xb - xc) * xc +(yb - yc) * yc == 0){
			angle = 1;
		}
		if(length == 1){
			if (angle == 1){
				printf("square\n");
			}
			else printf("diamond\n");
		}
		else {
			if (angle == 1){
				printf("rectangle\n");
			}
			else printf("other\n");
		}
	}
} 
