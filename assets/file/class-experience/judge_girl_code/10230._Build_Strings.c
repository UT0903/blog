#include <stdio.h>
#include <string.h>
 
int K, L, N;
char C[2], temp[1025];
void sort(char start, char temp[]){
    if(strlen(temp) == L){
        printf("%s\n", temp);
        //memset(temp, '\0', 1025);
        return;
    }
    for(int j = 1; j <= K; j++){
        strncat(temp, &start, 1);
        temp[strlen(temp)] = '\0';
        printf("temp1 = %s\n", temp);
        sort(start + j, temp);
        temp[strlen(temp) - 1] = '\0';
        printf("temp2 = %s\n", temp);
    }
    return;
}
int main(){
    scanf("%s%d%d%d", C, &K, &L, &N);
    //printf("+%c+\n", C[0]);
    sort(C[0], temp);
}