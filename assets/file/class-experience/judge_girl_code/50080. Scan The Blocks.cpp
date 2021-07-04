#include <stdio.h>
int main()
{
	int n, i, m;
	while(scanf("%d", &n) == 1){
		int fail = 0, higher = -10001, lower = 10001;
		for(i = 0;i < n;i++){
			if (scanf("%d", &m) == EOF){
				fail = 1;
				break;
			}
			if(m > higher) higher = m;
			if(m < lower) lower = m;
		}
	if(fail) printf("%d\n", lower);
	else printf("%d\n", higher);
	}
}


