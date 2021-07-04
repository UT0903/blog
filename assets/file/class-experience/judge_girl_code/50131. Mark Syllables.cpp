# include <stdio.h>
# include <string.h>
char string[10001];
int vowel[10001];
int cut[2];
char print[10001];
char a[10001];
int main(){
	while(scanf("%s", string) != EOF){
		int i;
		scanf("%d", &cut[0]);
		scanf("%d", &cut[1]);
		//printf("OK\n");
		int length = 0, k = 0;
		for(i = 0; string[i] != '\0'; i++){
			length++;
			if(string[i] =='a' || string[i] =='e' || string[i] =='i' || string[i] =='o' || string[i] =='u'){
				vowel[k] = i;
				k++;
			}
		}
		//printf("OK\n");
		memset(a, '0', 10001);
		for(int j = 0; j < 2; j++){
			k = 0;
			for(i = 0; i < ((cut[j] - 1 >= 0)? vowel[cut[j]-1] + 1 : 0 ); i++){
				printf("+");
				k++;
			}
			for(i = 0; i < ((cut[j] - 1 >= 0)? vowel[cut[j]] - vowel[cut[j] - 1] : vowel[cut[j]] + 1); i++){
				printf("%c", ((cut[j] - 1 >= 0)? string[i + vowel[cut[j] - 1] + 1] : string[i]));
				a[k] = '+';
				k++;
			}
			for(i = 0; i < length - vowel[cut[j]] - 1; i++){
				printf("+");
				k++;
			}
			printf("\n");
		}
		for(i = 0; i < length; i++){
			if(a[i] == '0') printf("%c", string[i]);
			else printf("+");
		}
		printf("\n");

		
		
		
		
	}
	
}
