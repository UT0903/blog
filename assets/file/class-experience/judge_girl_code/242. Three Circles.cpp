# include <stdio.h>

int main(){
	long long n, i, count = 0, one = 0, two = 0, three = 0, x1, y1, r1, x2, y2, r2, x3, y3, r3, x0, y0 ;
	scanf("%lld", &n);
	for(i = 0; i < n; i++){
		count = 0;
		one = 0;
		two = 0;
		three = 0;
		scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld", &x1, &y1, &r1, &x2, &y2, &r2, &x3, &y3, &r3);
		for (x0 = x1 - r1; x0 <= x1 + r1; x0++){
			for (y0 = y1 - r1; y0 <= y1 + r1; y0++){
				if ((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1) <= r1*r1){
					one++;
				}
			}
		}
		//printf("%d\n", one);
		for (x0 = x2 - r2; x0 <= x2 + r2; x0++){
			for (y0 = y2 - r2; y0 <= y2 + r2; y0++){
				if ((x0 - x2)*(x0 - x2) + (y0 - y2)*(y0 - y2) <= r2*r2){
					one++;
				}
			}
		}
		//printf("%d\n", one);
		for (x0 = x3 - r3; x0 <= x3 + r3; x0++){
			for (y0 = y3 - r3; y0 <= y3 + r3; y0++){
				if ((x0 - x3)*(x0 - x3) + (y0 - y3)*(y0 - y3) <= r3*r3){
					one++;
				}
			}
		}
		//printf("%d\n", one);
		if((x1 - x2)*(x1 - x2) + (y1- y2)*(y1 - y2) <= 400){
			for (x0 = (x1 + x2) / 2 - 30; x0 <= (x1 + x2) / 2 + 30; x0++){
				for (y0 = (y1 + y2) / 2 - 30; y0 <= (y1 + y2) / 2 + 30; y0++){
					if ((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1) <= r1*r1 && (x0 - x2)*(x0 - x2) + (y0 - y2)*(y0 - y2) <= r2*r2){
						two++;
					}
				}
			}	
		}
		//printf("%d\n", two);
		if((x3 - x2)*(x3 - x2) + (y3- y2)*(y3 - y2) <= 400){
			for (x0 = (x3 + x2) / 2 - 30; x0 <= (x3 + x2) / 2 + 30; x0++){
				for (y0 = (y3 + y2) / 2 - 30; y0 <= (y3 + y2) / 2 + 30; y0++){
					if ((x0 - x3)*(x0 - x3) + (y0 - y3)*(y0 - y3) <= r3*r3 && (x0 - x2)*(x0 - x2) + (y0 - y2)*(y0 - y2) <= r2*r2){
						two++;
					}
				}
			}	
		}
		//printf("%d\n", two);
		if((x3 - x1)*(x3 - x1) + (y3- y1)*(y3 - y1) <= 400){
			for (x0 = (x3 + x1) / 2 - 30; x0 <= (x3 + x1) / 2 + 30; x0++){
				for (y0 = (y3 + y1) / 2 - 30; y0 <= (y3 + y1) / 2 + 30; y0++){
					if ((x0 - x3)*(x0 - x3) + (y0 - y3)*(y0 - y3) <= r3*r3 && (x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1) <= r1*r1){
						two++;
					}
				}
			}	
		}
		//printf("%d\n", two);
		if((x3 - x1)*(x3 - x1) + (y3- y1)*(y3 - y1) <= 400 && (x3 - x2)*(x3 - x2) + (y3- y2)*(y3 - y2) <= 400 && (x1 - x2)*(x1 - x2) + (y1- y2)*(y1 - y2) <= 400){
			for (x0 = (x3 + x1 + x2) / 3 - 100; x0 <= (x3 + x1 + x2) / 3 + 100; x0++){
				for (y0 = (y3 + y1 + y2) / 3 - 100; y0 <= (y3 + y1 + y2) / 3 + 100; y0++){
					if ((x0 - x3)*(x0 - x3) + (y0 - y3)*(y0 - y3) <= r3*r3 && (x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1) <= r1*r1 && (x0 - x2)*(x0 - x2) + (y0 - y2)*(y0 - y2) <= r2*r2){
						three++;
					}
				}
			}	
		}
		//printf("%d\n", three);
		count = one - 2 * two + 4 * three;
		printf("%lld\n", count);
	}
}
