# include <stdio.h>
# include <ctype.h>

int main(){
	int num = 0, alp = 0, vow = 0, con = 0;
	char c;
	while(scanf("%c", &c) != EOF){
		if(isdigit(c)) num++;
		if(isalpha(c)){
			alp++;
			c = tolower(c);
			if(c =='a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
				vow++;
			}
			else con++;
		}
	}
	printf("%d %d %d %d", num, alp, vow, con);
}
