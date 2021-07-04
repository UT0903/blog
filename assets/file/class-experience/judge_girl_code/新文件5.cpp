#include <stdio.h>

char a[100];
int main(){
	int i;
	while(scanf("%s", a) != EOF){
		for(i = 0; a[i] != '\0'; i++){
			if(a[i] == 'p') a[i] = '1';
			else if(a[i] == 'q') a[i] = '2';
		}
		printf("%s\n", a);
		for(i = 0; a[i] != '\0'; i++){
			a[i] = '\0';
		}
	}
}
