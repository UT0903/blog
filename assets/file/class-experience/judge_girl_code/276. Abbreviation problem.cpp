# include <stdio.h>
# include <string.h>
# include <ctype.h>


int Check(char string[]){
	//printf("string = %s\n", string);

	if(strcmp("of", string) == 0 || strcmp("and", string) == 0 || strcmp("the", string) == 0 || strcmp("at", string) == 0){
		//printf("0\n");
		return 0;
	}
	else{
		//printf("1\n");
		return 1;
	}
}
char string[128];
char abbr[128];

int main(){
	int k = 0;
	while(scanf("%s", string) != EOF){
		int endline = 0;
		if(string[strlen(string) - 1] == '.'){
			//printf("%c\n", string[strlen(string) - 1]);
			endline = 1;
			string[strlen(string) - 1] = '\0';
		}
		int l = -1;
		l = Check(string);
		//printf("%d\n", l);
		if(l == 1){
			
			abbr[k] = toupper(string[0]);
			k++;
		}
		if(endline == 1){
			printf("%s\n", abbr);
			memset(abbr, '\0', 128);
			k = 0;
		}
		memset(string, '\0', 128);
	}
}
