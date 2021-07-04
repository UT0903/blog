# include <stdio.h>
# include <string.h>
char string[260];
char print[260];
char temp[260][260];



void Typeset(char print[260], char temp[][260], int limit, int word, int length){
	int i;
	char space[3] = {' '};
	/*printf("word = %d, length = %d\n", word, length);
	printf("temp = ");
	for(i = 0; i < word; i++){
		printf("%s ", temp[i]);
	}
	printf("\n");
	*/
	if(word - 1 != 0){
		for(i = 0; i < limit - length; i++){
			strcat(temp[i % (word-1)], space);
		}
	//printf("ans : ");
		for(i = 0; i < word; i++){
			printf("%s", temp[i]);
		}
		printf("\n");
	}
	else if(word == 1){
		printf("%s", temp[i]);
		for(i = 0; i < limit - length; i++){
			printf(" ");
		}
		printf("\n");
	}
}

int main(){
	int length = 0, word = 0;
	int limit, k = 0;
	scanf("%d", &limit);
	
	while(scanf("%s", string) != EOF){
		//printf("OK\n");
		word++;
		length += strlen(string);
		if(length + (word - 1) <= limit){
			strcpy(temp[k], string);
			k++;
		}
		else if(length + (word - 1) > limit){
			Typeset(print, temp, limit, word - 1, length - strlen(string));
			k = 0;
		//	memset(print, '\0', 260);
			word = 1;
			length = strlen(string);
		//	memset(temp,'\0', *257);
			
			strcpy(temp[k], string);
			k++;
		}
	}
	/*int l;
	printf("word = %d, length = %d\n", word, length);
	printf("temp = ");
	for(l = 0; l < word; l++){
		printf("%s ", temp[l]);
	}
	printf("\n");*/
	Typeset(print, temp, limit, word, length);
}
