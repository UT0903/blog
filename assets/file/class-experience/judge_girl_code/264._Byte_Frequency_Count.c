#include <stdio.h>
#include <assert.h>
int temp[70000];
int max = -1;
int most = -1;
short num[10000000];
char filename[128];
int main(){
	scanf("%s", filename);
	FILE *fp;
	fp = fopen(filename, "rb");
	assert(fp != NULL);
	int c[1];
	
	fread(c, sizeof(int), 1, fp);
	fread(num, sizeof(short), c[0], fp);
	//printf("73808 = %d\n", num[73808]);
	for(int i = 0; i < c[0]; i++){
		//printf("i = %d\n", i);

		temp[num[i] + 35000]++;
	}
	//printf("OK\n");
	fclose(fp);
	for(int i = 0; i < 70000; i++){
		if(temp[i] >= most){
			max = i;
			most = temp[i];
		}
	}
	printf("%d\n%d\n", max - 35000, most);
}