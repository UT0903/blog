#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct ep{
	int year;
	int month;
	int day;
	char cat[32];
	int amount;
}EP;
EP expence[10000];
int cmp(const void *data1, const void *data2){
	EP *tmp1 = (EP *) data1;
	EP *tmp2 = (EP *) data2;
	if(tmp1->year < tmp2->year) return -1;
	else if(tmp1->year > tmp2->year) return 1;
	else if(tmp1->month < tmp2->month) return -1;
	else if(tmp1->month > tmp2->month) return 1;
	else if(tmp1->day < tmp2->day) return -1;
	else if(tmp1->day > tmp2->day) return 1;
	else return strcmp(tmp1->cat, tmp2->cat);
}
int compare(EP a, EP b){
	if(a.year == b.year && a.month == b.month && a.day == b.day && strcmp(a.cat, b.cat) == 0) return 1;
	return 0;
}
int main(){
	int i = 0;
	while(scanf("%d %d %d %s %d", &expence[i].year, &expence[i].month, &expence[i].day, expence[i].cat, &expence[i].amount) != EOF)
		i++;
	qsort(expence, i, sizeof(EP), cmp);
	//printf("----------\n");
	for(int j = 0; j < i; j++){
		if(j + 1 < i && compare(expence[j], expence[j + 1])){
			expence[j + 1].amount += expence[j].amount;
		}
		else printf("%d %d %d %s %d\n", expence[j].year, expence[j].month, expence[j].day, expence[j].cat, expence[j].amount);
	}
}