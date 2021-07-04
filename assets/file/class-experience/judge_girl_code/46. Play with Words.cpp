# include <stdio.h>
# include <string.h>
# include <stdlib.h>

char *temp[100];
char string[100];
char ans[1000000];
char fake[1000000];
char line[10000];
int count[10000];
int main(){
	while(fgets(string,99,stdin) != NULL){
		
		temp[0] = strtok(string, " ");
		temp[1] = strtok(NULL, " \n");
		temp[2] = strtok(NULL, "\n ");
		if(strcmp(temp[0] , "insert") == 0){
			if(strcmp(temp[1] , "right") == 0){
				strcat(ans, temp[2]);
			}
			else if(strcmp(temp[1] , "left") == 0){
				strcpy(fake, ans);
				strcpy(ans, temp[2]);
				strcat(ans, fake);
				/*strcpy(&ans[1], ans);
				strncpy(ans, temp[2], 1);*/
			}
			else{
				char *tem;
				/*printf("temp[1] = %d\n",atoi(temp[1]));
				printf("strlen(ans) = %d\n", strlen(ans));
				printf("ans = %s\n", ans);*/
				strcpy(fake, &ans[atoi(temp[1]) - 1]);
				strcpy(&ans[atoi(temp[1])-1], temp[2]);
				strcat(ans, fake);
				//strcpy(ans + atoi(temp[1]), ans + (atoi(temp[1]) - 1));
				//printf("ans = %s\n", ans);
				/*strncpy(&ans[atoi(temp[1]) - 1], temp[2], 1);
				printf("ans = %s\n", ans);
				strcpy(&ans[atoi(temp[1])], tem);
				printf("ans = %s\n", ans);*/
				
			}
		}
		else if(strcmp(temp[0] ,"delete") == 0){
			//printf("in\n");
			if(strcmp(temp[1] ,"right") == 0){
				//printf("strlen(ans) = %d\n", strlen(ans));
				ans[strlen(ans) - 1] = '\0';
			}
			else if(strcmp(temp[1] ,"left") == 0){
				strcpy(ans, &ans[1]);
			}
			else{
				strcpy(&ans[atoi(temp[1]) - 1], &ans[atoi(temp[1])]);
			}
		}
		printf("%s\n", ans);
	}
	int max = 0, i, k = 0;
	//printf("%d\n", strlen(ans)-1);
	int len = strlen(ans);
	for(i = 0 ; i < len - 2; i++){
		//printf("fuck);
		if(ans[i] != ans[i + 1]){
			line[k] = ans[i];
			count[k]++;
			k++;
		}
		else count[k]++;
	}
	//printf("k = %d\n", k);
	for(i = 0; i <= k; i++){
		if(count[i] > max) max = count[i];
	}
	for(i = 0; i < k; i++){
		if(count[i] == max) printf("%c ", line[i]);
	}
	//printf("%d", max);
	
	printf("%d\n", max);
}
