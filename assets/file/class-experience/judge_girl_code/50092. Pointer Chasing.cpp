#include <stdio.h>
#include <ctype.h>
#include <string.h>
//#include "chasing.h"

void chasing(int **A[], int a, int *B[], int b, int C[], int c){
	char str[64];
	char od[2];
	char *iptr;
	memset(str, '\0', 64);
	memset(A, 0, sizeof(A[0])*a);
    memset(B, 0, sizeof(B[0])*b);
	while( fgets(str, 64, stdin) != NULL){
		memset(od, '\0', 2);
		iptr = &str[0];
		while(*iptr == ' '){
			//printf("OK");
			iptr++;
		}
		
		if(!isupper(*iptr)) {
			printf("0\n");
			continue;
		}
		if(*iptr !='A' && *iptr != 'B') {
			printf("0\n");
			continue;
		}
		if(*(iptr+1) != ' ') {
			printf("0\n");
			continue;
		}
		od[0] = *iptr;
		//printf("od[0] = %c\n", od[0]);
		iptr++;
		while(*iptr == ' '){
			//printf("OK");
			iptr++;
		}
		int num1 = 0;
		char *temp_iptr;
		temp_iptr = iptr;
		int stop = 0;
		while(*temp_iptr != ' '){
			if(!isdigit(*temp_iptr)){
				stop = 1;
				break;
			}
			temp_iptr++;
			//printf("OK");
		}
		if(stop) {
			printf("0\n");
			continue;
		}
		int i, length = temp_iptr - iptr;
		//printf("temp_iptr - iptr = %d\n", temp_iptr - iptr);
		for(i = 0; i < length; i++){
			num1 += *iptr - 48;
			iptr++;
			if(i != length - 1){
				num1 = num1 * 10;
			}
			//printf("num1 = %d\n", num1);
		}
		//printf("iptr = %c", iptr);
		while(*iptr == ' '){
			//printf("OK");
			iptr++;
		}
		if(!isupper(*iptr)) {
			printf("0\n");
			continue;
		}
		if(*iptr !='B' && *iptr != 'C') {
			printf("0\n");
			continue;
		}
		if(*(iptr+1) != ' ') {
			printf("0\n");
			continue;
		}
		if((*iptr == 'B' && od[0] != 'A') || (*iptr == 'C' && od[0] != 'B')) {
			printf("0\n");
			continue;
		}
		od[1] = *iptr;
		//printf("od[1] = %c\n", od[1]);
		iptr++;
		while(*iptr == ' '){
			//printf("OK");
			iptr++;
		}
		
		int num2 = 0;
		char *temp2_iptr;
		temp2_iptr = iptr;
		stop = 0;
		while(*temp2_iptr != ' ' && *temp2_iptr != '\n'){
			//printf("temp2_iptr = +%c+\n", *temp2_iptr);
			if(!isdigit(*temp2_iptr)){
				stop = 1;
				break;
			}
			temp2_iptr++;
			//printf("OK");
		}
		if(stop) {
			printf("0\n");
			continue;
		}
		length = temp2_iptr - iptr;
		//printf("temp2_iptr - iptr = %d\n", temp2_iptr - iptr);
		for(i = 0; i < length; i++){
			num2 += *iptr - 48;
			iptr++;
			if(i != length - 1){
				num2 = num2 * 10;
			}
			//printf("num2 = %d\n", num2);
		}
		if((num1 >= a && od[0] == 'A') || (num1 >= b && od[0] == 'B')) {
			printf("0\n");
			continue;
		}
		if((num2 >= b && od[1] == 'B') || (num2 >= c && od[1] == 'C')) {
			printf("0\n");
			continue;
		}
		//printf("iptr = +%c+\n", *iptr);
		stop = 0;
		while(*iptr != '\n' && iptr - str < 64){
			if(*iptr != ' '){
				
				stop = 1;
				break;
			}
			iptr++;
		}
		if(stop){
			printf("0\n");
			continue;
		}
		
		if(od[0] == 'A' && od[1] == 'B'){
			printf("1\n");
			A[num1] = &B[num2];
		}
		else if(od[0] == 'B' && od[1] == 'C'){
			printf("1\n");
			B[num1] = &C[num2];
		}
	}
	
}


#include <stdio.h>
//#include "chasing.h"
int main() {
        int a = 3, b = 3, c = 3;
        int **A[3] = {}, *B[3] = {}, C[3] = {2, 1, 4};
        chasing(A, a, B, b, C, c);
 
        int **ansA[3] = {} ,*ansB[3] = {};
        for (int i = 0; i < a; i++)
                ansA[i] = NULL;
        for (int i = 0; i < b; i++)
                ansB[i] = NULL;
        ansA[0] = &B[1];;
        /*Check A*/
        for (int i = 0; i < a; i++)
                if (A[i] != ansA[i] )
                        printf("A[%d] wrong answer!\n", i);
 
        /*Check B*/
        for (int i = 0; i < b; i++)
                if (B[i] != ansB[i] )
                        printf("B[%d] wrong answer!\n", i);
        return 0;
 
}
