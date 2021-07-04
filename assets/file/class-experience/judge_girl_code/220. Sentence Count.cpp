# include <stdio.h>
char a;
int count, i = 0;
int main(){
	int stc = 0;
	while(scanf("%c", &a) != EOF){
		if((a == '\n'|| a == '\0') && count == 1){
			stc++;
			count = 0;
		}
		else if (count == 1 && a == ' '){
			count = 2;
		}
		else if(count == 2 && a == ' '){
			stc++;
			count = 0;
		}
		else if(a == '.'){
			count = 1;
		}
		else {
			count = 0;
		}	
	}
	printf("%d", stc);
}
