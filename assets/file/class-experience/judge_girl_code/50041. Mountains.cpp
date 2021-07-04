# include <stdio.h>
# include <stdlib.h>

int main(){
	int n, h, pre_h, pre_pre_h, cost, i;
	scanf("%d", &n);
	scanf("%d %d", &pre_h, &h);
	if (h - pre_h > 0) cost = abs(h - pre_h) * 3;
	else if (h - pre_h <= 0) cost = abs(h - pre_h) * 2;
	pre_pre_h = pre_h;
	pre_h = h;
	for(i = 0 ; i < n-2 ; i++){
		scanf("%d", &h);
		if (h - pre_h > 0){
			if (pre_h - pre_pre_h > 0 ) cost += abs(h - pre_h) * 4;
			else if (pre_h - pre_pre_h <= 0 ) cost += abs(h - pre_h) * 3;
		}
		else if (h - pre_h <= 0){
			if (pre_h - pre_pre_h > 0 ) cost += abs(h - pre_h) * 3;
			else if (pre_h - pre_pre_h <= 0 ) cost += abs(h - pre_h) * 2;
		}
		pre_pre_h = pre_h;
		pre_h = h;
		
	}
	printf("%d", cost);
} 
