# include <stdio.h>
# include <string.h>
char *a, *b;
int main(){
	scanf("%s", a);
	strcpy(b,a);
	printf("%s", b);
}

while(fgets(input, 499, stdin) != NULL){
		i = 0;
		temp[i] = strtok(input, " ");
		printf("OK");
		while(temp[i] != NULL && *temp[i] !='\n'){
			i++;
			temp[i] = strtok(NULL, " ");
			strcpy(line[j][i], temp[i]);
			printf("line[%d][%d] = +%s+\n", j, i, line[j][i]);
		}
		
		j++;
	}
