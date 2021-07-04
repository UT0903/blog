# include <stdio.h>
# include <string.h>
char input[1025];
char senten[1025];
char A[501];
char B[501];
char delim[2];
main(){
	scanf("%s", senten);
	while(scanf("%s", input) != EOF){
		if(input[0] == 'p'){
			printf("%s\n", senten);
		}
		else{
			strncpy(delim , &input[1], 1);
			delim[1] = '\0';
			char *ptr;
			ptr = strtok(&input[1], delim);
			strcpy(A, ptr);
			ptr = strtok(NULL, delim);
			strcpy(B, ptr);
			//printf("OK");
			//printf("A = %s, B = %s", A, B);
			ptr = strstr(senten, A);
			if(ptr != NULL){
				strcpy(ptr + strlen(B), ptr + strlen(A));
				strncpy(ptr, B, strlen(B));
			}
			
		}
		memset(input, '\0', 1025);
		memset(delim, '\0', 2);
		
			
			
		
	}
}
