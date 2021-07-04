# include <stdio.h>
# include <string.h>
char a[1000000];
char string[128];
int main(){
	int i;
	scanf("%s", string);
	strcat(a , string);
	while(scanf("%s", string) != EOF){
		int fin = 0;
		for(i = strlen(string) - 1; i >= 0; i--){
			//printf("strlen(string) - 1 = %d\n", strlen(string) - 1);
			if(strncmp( &a[strlen(a) - i - 1], string, i + 1) == 0){
				strcpy(&a[strlen(a) - i - 1], string);
				//printf("a = %s\n", a);
				fin = 1;
				break;
			}
		}
		if(fin == 0){
			strcat(a, string);
			//printf("a = %s\n", a);
		}
		//printf("fin = %d\n", fin);
		for(i = 0; i < 128; i++){
			string[i] = '\0';
		}
	}
	printf("%s", a);
}
