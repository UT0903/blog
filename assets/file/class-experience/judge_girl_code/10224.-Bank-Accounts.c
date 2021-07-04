# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
 
char user[33][128];
int balance[33];
char *temp[5];
char input[110];
char a;
int main(){
    int n, i = 0, j = 0, count = 0, k = 0, ok = 0;
    scanf("%d", &n);
    scanf("%c", &a);
    while(fgets(input, 100, stdin) != NULL){
        /*for (int p = 0 ; p < 5; p ++){
            temp[p] = NULL;
        }*/
        i = 0;
        memset(temp, '\0', 4);
        char *del =" "; 
        temp[0] = strtok(input, del);
       // printf("%s\n", *temp);
        while(temp[i] != NULL){
            i++;
            temp[i] = strtok(NULL, del);
		}
        if(temp[0] != NULL && count < n){
            //printf("%s\n", temp[1]);
            strcpy(user[k], temp[0]);
            //printf("user = %s\n", user[k]);
            balance[k] = atoi(temp[1]);
            //printf("balance = %d\n", balance[k]);
            k++;
            count++;
            continue;
        }
        if(temp[3] == NULL){
            //printf("here\n");
            //printf("%s\n", temp[1]);
            ok = 0;
            for(i = 0; i < n; i++){
                if(strcmp(user[i], temp[0]) == 0) {
                	ok = 1;
					break;
				}
            }
            if(!ok) continue;
 
            if(strstr(temp[1], "earns") != NULL) {
                //printf("i = %d\n", i);
                balance[i] += atoi(temp[2]);
                //printf("%d\n", balance[i]);
            }
            else if(strstr(temp[1], "spends") != NULL) {
                if(balance[i] - atoi(temp[2]) < 0) continue;
                else balance[i] -= atoi(temp[2]);
            }
            else if(strstr(temp[1], "becomes") != NULL){
                if(atoi(temp[2]) < 0) continue;
                else balance[i] = atoi(temp[2]);
            }
            else continue;
        }
        else{
        	ok = 0;
            for(i = 0; i < n; i++){
                if(strcmp(user[i], temp[0]) == 0) {
                	ok = 1;
					break;
				}
            }
            if(!ok) continue;
            ok = 0;
            for(j = 0; j < n; j++){
                if(strcmp(user[j], temp[2]) == 0) {
                	ok = 1;
                	break;
				}
            }
            if(!ok) continue;
            if(strstr(temp[1], "gives") != NULL ){
                if(balance[i] - atoi(temp[3]) < 0) continue;
                else {
                    balance[i] -= atoi(temp[3]);
                    balance[j] += atoi(temp[3]);
                }
            }
        }
        //memset(temp, '\0', 4);
    }
    int x;
    for(x = 0; x < n; x++){
		printf("%s %d\n", user[x], balance[x]);
    }
 
 
 
}
