#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
int main(){
	bool check1 = 0, check2 = 0;
	bool carry = 0;
	int n = 1;
	FILE *fp1, *fp2, *fpout;
	fp1 = fopen("0.bin", "rb");
	assert(fp1 != NULL);
	fp2 = fopen("1.bin", "rb");
	assert(fp1 != NULL);
	fpout = fopen("0.txt", "wb");
	assert(fpout != NULL);
	while((check1 = fseek(fp1, -n, SEEK_END)) == 0 || (check2 = fseek(fp2, -n, SEEK_END)) == 0){
		int a = 0, b = 0;
		if(!check1)fread(&a, 1, 1, fp1);
		if(!check2)fread(&b, 1, 1, fp2);
		fwrite(&a, 1, 1, stdout);
		printf("------");
		//printf("size = %lu\n", sizeof(unsigned char));
		printf("a = %d, b = %d\n", a, b);
		int ans = (a + b + carry) % 256;
		printf("ans = %d\n", ans);
		carry = (a + b) / 256;
		fwrite(&ans, 1, 1, fpout);
		rewind(fpout);
		n++;
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fpout);



}