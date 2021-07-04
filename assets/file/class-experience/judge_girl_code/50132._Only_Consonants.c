#include <stdio.h>
#include <string.h>
#define MAXN 500000
char buf[MAXN];
int Judge(char x){
	return (x == '\n' || x ==' ' || x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u');
}
int Compare(char a, char b){
	return (a < b);
}
int main(){
	int c;
	int cnt = 0;
	char last = 127;
	while(scanf("%s", buf) != EOF){
		int len = strlen(buf);
		for(int i = 0; i < len; i++){
			if(Judge(buf[i]))
				continue;
			else{
				if(Compare(last, buf[i]))
					cnt++;
				last = buf[i];
			}
		}
	}
	printf("%d\n", cnt);
}