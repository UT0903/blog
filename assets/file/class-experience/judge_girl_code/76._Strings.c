#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char string[64][40];
char *string_ptr[64];
int cmp(const void *data1, const void *data2){
	return strcmp(*((char **) data1), *((char **) data2));
}
int main(){
	int i = 0;
	while(fgets(string[i], 40, stdin) != NULL){
		string_ptr[i] = string[i];
		i++;
	}
	//printf("OK1\n");
	qsort(string_ptr, i, sizeof(char *), cmp);
	//printf("OK\n");
	for(int j = 0; j < i; j++){
		fputs(string_ptr[j], stdout);
		//printf("\n");
	}

}