# include <stdio.h>
# include <string.h>
int count[26][26];
char input[30];
char train[120];
int full[26] = {0};
int main(){
	int n, i, j;
	scanf("%d", &n);
	while(~scanf("%s", input)){
		for(i = 0; i < strlen(input) - 1; i++){
			count[input[i] - 'a'][input[i+1] - 'a']++;
		}
	}
	int max = -1, max_i = -1, max_j = -1;
	for(i = 0; i < 26; i++){
		for(j = 0; j < 26; j++){
			printf("%d%s", count[i][j], (j == 25)? "\n" : " ");
			if(count[i][j] > max){
				max = count[i][j];
				max_i = i;
				max_j = j;
			}
		}
	}
	printf("%c", max_i + 'a');
	full[max_i] = 1;
	
	while(1){
		max_i = max_j;
		max = -1;
		full[max_i] = 1;
		for(j = 0; j < 26; j++){
			if(count[max_i][j] > max && count[max_i][j] > n && full[j] == 0){
				max_j = j;
				max = count[max_i][j];
			}
		}
		if(max == -1) {
			printf("%c", max_i + 'a');
			break;
		}
		printf("%c", max_i + 'a');
		//max_i = max_j;
		
		
	}
	printf("\n");
	
} 
