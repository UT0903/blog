#include <stdio.h>
#include <stdlib.h>
typedef struct date
{
	int year;
	int month;
	int day;
}Date;
int compare(const void *data1, const void *data2){
	Date *tmp1 = (Date *) data1;
	Date *tmp2 = (Date *) data2;
	if(tmp1->year < tmp2->year) return -1;
	else if(tmp1->year > tmp2->year) return 1;
	else if(tmp1->month < tmp2->month) return -1;
	else if(tmp1->month > tmp2->month) return 1;
	else if(tmp1->day < tmp2->day) return -1;
	else if(tmp1->day > tmp2->day) return 1;
	else return 0;
}
Date a[1000000];
int main(){
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d %d %d", &a[i].year, &a[i].month, &a[i].day);
	}
	qsort(a, n, sizeof(Date), compare);
	for(int i = 0; i < n; i++){
		printf("%d %d %d\n", a[i].year, a[i].month, a[i].day);
	}
}