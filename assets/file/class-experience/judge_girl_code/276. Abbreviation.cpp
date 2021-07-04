# include <stdio.h>
# include <string.h>
# include <ctype.h>
char string[128];
char abbr[128];

int check(char string[]){
	if(string != "of" && string != "and" && string != "the" && string != "at"){
		return 1;
	}
	else{
		return 0;
	}
}

int main(){
	int k = 0;
	while(scanf("%s", string) != EOF){
		int endline = 0;
		if(string[strlen(string) - 1] == '.'){
			endline = 1;
			string[strlen(string) - 1] = '\0';
		}
		if(check(string)){
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
