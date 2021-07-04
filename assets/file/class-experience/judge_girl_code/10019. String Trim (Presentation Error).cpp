# include <stdio.h>
# include <ctype.h>
int a[101] = {0};
int main(){
	char c;
	int i;
	while(scanf("%c", &c) != EOF){
		if(c != '\n'){
			a[i] = c;
			i++;
		}
		else{
			int start = 0, end = i - 1;
			while(isspace(a[start])) start++;
			while(isspace(a[end])) end--;
			int x;
			for(x = start; x <= end; x++){
				printf("%c", a[x]);
			}
			printf("\n");
			i = 0;
		}
		
			
	}
}
