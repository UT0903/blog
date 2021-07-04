# include <stdio.h>
# include <string.h>
# include <stdlib.h>
int varnum;
char input[10000], *temp[310] , line[1001][310][20];
char variable[310][20];
int value[101];
int main(){
	fgets(input, 9999, stdin);
	int i = 0;
	temp[i] = strtok(input, " ");
	while(temp[i] != NULL){
		i++;
		temp[i] = strtok(NULL, " ");
		//printf("+%s+\n", temp[i]);
	}
	int k = 0;
	i = 0;
	//printf("OK\n");
	while(strcmp(temp[i], "END\n") != 0){
		if(i % 3 == 0){
			
			strcpy(&variable[k][0], temp[i]);
		//	printf("variable[%d] = %s  ", k, variable[k]);
			
		}
		else if(i % 3 == 2){
			value[k] = atoi(temp[i]);
			varnum++;
		//	printf("value[%d] = %d\n", k, atoi(temp[i]));
			k++;
		}
		i++; 
	}
	int j = 1;
	char *ptr;
	while(fgets(input, 9999, stdin) != NULL){                               
		input[strlen(input) - 1] = ' ';
		i = 0;
		ptr = strtok(input, " ");
		while(ptr != NULL){
			strcpy(line[j][i], ptr);
		//	printf("line[%d][%d] = +%s+\n", j, i, line[j][i]);
			i++;
			ptr = strtok(NULL, " ");
			
		}
		j++;
	}
	
	int count = i, x;
	i = 1, j = 0;
	int var1, var2, var;
	//printf("OK");
	int stop = 0;
	while(strcmp(line[i][0], "STOP") != 0){
		stop++;
		if(strcmp(line[i][0], "IF") == 0){
		//	printf("if\n");
			int skip = 0;
			for(x = 0; variable[x] != NULL; x++){
				//printf("x = %d\n", x);
				if(strcmp(line[i][1], variable[x]) == 0){
					var1 = x;
					skip++;
		//			printf("var1 = %d , skip = %d\n", var1, skip);
				}
				if(strcmp(line[i][3], variable[x]) == 0){
					var2 = x;
					skip++;
		//			printf("var2 = %d , skip = %d\n", var2, skip);
				}
				if(skip == 2) break;
			}
			int judge = 0;
			if(strcmp(line[i][2], ">=") == 0){
				if(value[var1] >= value[var2]) judge = 1;
			}
			else if(strcmp(line[i][2], "<=") == 0){
				if(value[var1] <= value[var2]) judge = 1;
			}
			else if(strcmp(line[i][2], ">") == 0){
				if(value[var1] > value[var2]) judge = 1;
			}
			else if(strcmp(line[i][2], "<") == 0){
				if(value[var1] < value[var2]) judge = 1;
			}
			else if(strcmp(line[i][2], "==") == 0){
				if(value[var1] == value[var2]) judge = 1;
			}
			else if(strcmp(line[i][2], "!=") == 0){
				if(value[var1] != value[var2]) judge = 1;
			}
		//	printf("judge = %d\n", judge);
			if(judge){
				i = atoi(line[i][5]);
				
			}
			else{
				i++;
			}
		}
		else if(strcmp(line[i][0], "PRINT") == 0){
		//	printf("PRINT\n");
			
			for(x = 0; variable[x] != NULL; x++){
				if(strcmp(line[i][1], variable[x]) == 0){
					var = x;
					break;
				}
			}
			printf("%d\n", value[var]);
			i++;
		}
		else if(strcmp(line[i][0], "GOTO") == 0){
			//printf("GOTO\n");
			i = atoi(line[i][1]);
		}
		else{
			//printf("else\n");
			int skip = 0;
			for(x = 0; variable[x] != NULL; x++){
			//	printf("OK\n");
				if(strcmp(line[i][2], variable[x]) == 0){
					var1 = x;
					skip++;
				}
				if(strcmp(line[i][4], variable[x]) == 0){
					var2 = x;
					skip++;
				}
				if(strcmp(line[i][0], variable[x]) == 0){
					var = x;
					skip++;
				}
				if(skip == 3) break;
			}
			//printf("var = %d, var1 = %d, var2 = %d\n", var, var1, var2);
			if(strcmp(line[i][3], "+") == 0){
				value[var] = value[var1] + value[var2];
			}
			else if(strcmp(line[i][3], "-") == 0){
				value[var] = value[var1] - value[var2];
			}
			else if(strcmp(line[i][3], "*") == 0){
				value[var] = value[var1] * value[var2];
			}
			else if(strcmp(line[i][3], "/") == 0){
				value[var] = value[var1] / value[var2];
			}
			else if(strcmp(line[i][3], "%") == 0){
				value[var] = value[var1] % value[var2];
			}
			i++;
		}
		/*int l;
		for(l = 0; l < varnum; l++){
			printf("variable[%d] = %s, value[%d] = %d\n", l, variable[l], l, value[l]);
		}
		printf("i = %d\n", i);*/
	}
	return 0;
	
}
