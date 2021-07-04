#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int count = 0;
void compare(char *a, char *b){
	if(*a == '\0' && *b =='\0'){
		//printf("finish\n");
		return;
	}
	if(*a == *b){
		//printf("in\n");
		compare(a + 1, b + 1);
	}
	else{
		//printf("out\n");
		if(*a != '\0')compare(a + 1, b);
		if(*b != '\0')compare(a, b + 1);
		count++;
	}
	return;
}
char a[100][11];
int main(){
	int num = 0;
	int min = 10000000, min_i = 10000000, min_j = 10000000;
	while(scanf("%s", a[num]) != EOF) num++;
	for(int i = 0; i < num; i++){
		for(int j = i + 1; j < num; j++){
			count = 0;
			compare(a[i], a[j]);
			printf("i = %d, j = %d, count = %d\n", i, j, count);
			if(count < min){
				min = count;
				min_i = i;
				min_j = j;
			}
		}
	}
	printf("%d %d %d\n", min, min_i + 1, min_j + 1);

}