#include <stdio.h>
int main(){
	int prev2 = 0,prev = 0, now = 0, len = 0, start_idx, l_len = 0, max = 0;
	if(scanf("%d", &now) == EOF){
		printf("0\n");
	}
	else{
		start_idx = 1;
		prev = now;
		if(scanf("%d", &now) == EOF){
			printf("0\n");
		}
		else{
			prev2 = prev;
			prev = now;
			len = 2;
			while(scanf("%d", &now) != EOF){
				if(now > prev){
					if(prev > prev2){
						len++;
					}
					else{
						l_len = len;
						len = cnt;
					}
				}
				else{
					if(prev > prev2){
						l_len = len;
						len = 0;
					}
					else{
						len++;
					}
				}
			}
		}
	}
}