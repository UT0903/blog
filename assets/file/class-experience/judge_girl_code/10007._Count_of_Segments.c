#include <stdio.h>
int main(){
	int n;
	while(scanf("%d", &n) != EOF){
		int count = 0, fir, sec;
		scanf("%d", &fir);
		for(int i = 0; i < n - 1; i++){
			scanf("%d", &sec);
			if(fir != sec){
				count++;
			}
			fir = sec;
		}
		printf("%d\n", count + 1);
	}
}