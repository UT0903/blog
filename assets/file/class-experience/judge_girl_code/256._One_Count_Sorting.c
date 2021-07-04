#include <stdio.h>
#include <stdlib.h>
typedef unsigned long long int ULL;
ULL a[1000];
int compare(const void *data1, const void *data2){
	ULL *a = (ULL *)data1;
	ULL *b = (ULL *)data2;
	ULL tmp1 = *a;
	ULL tmp2 = *b;
	int count1 = 0, count2 = 0;
	for(int i = 0; i < 64; i++){
		//printf("OK\n");
		if((tmp1 & (ULL) 1) == (ULL) 1) count1++;
		if((tmp2 & (ULL) 1) == (ULL) 1) count2++;
		tmp1 = tmp1 >> 1;
		tmp2 = tmp2 >> 1;
	}
	if(count1 < count2) return -1;
	else if(count1 > count2) return 1;
	else{
		if(*a < *b) return -1;
		else if(*a > *b) return 1;
		else return 0;
	}
}
int main(){
	int i = 0;
	while(scanf("%llu", &a[i]) != EOF) i++;
	//printf("i = %d\n", i);
	qsort(a, i, sizeof(ULL), compare);
	for(int j = 0; j < i; j++){
		printf("%llu\n", a[j]);
	}
}