#include <stdio.h>

void Print_rank(int i){
	if(i >= 0 && i < 60) printf("F ");
	else if(i < 63)	printf("C- ");
	else if(i < 67)	printf("C ");
	else if(i < 70) printf("C+ ");
	else if(i < 73) printf("B- ");
	else if(i < 77) printf("B ");
	else if(i < 80) printf("B+ ");
	else if(i < 85) printf("A- ");
	else if(i < 90) printf("A ");
	else if(i <= 100) printf("A+ ");
	else printf("wrong");
	return;
}
double Search_rank(int i){
	if(i >= 0 && i < 60) return 0;
	else if(i < 63)	return 1.7;
	else if(i < 67)	return 2.0;
	else if(i < 70) return 2.3;
	else if(i < 73) return 2.7;
	else if(i < 77) return 3.0;
	else if(i < 80) return 3.3;
	else if(i < 85) return 3.7;
	else if(i < 90) return 4.0;
	else if(i <= 100) return 4.3;
	else printf("wrong");
	return -1;
}
double Search_score(int i){
	if(i >= 0 && i < 60) return 50;
	else if(i < 63)	return 60;
	else if(i < 67)	return 65;
	else if(i < 70) return 68;
	else if(i < 73) return 70;
	else if(i < 77) return 75;
	else if(i < 80) return 78;
	else if(i < 85) return 82;
	else if(i < 90) return 87;
	else if(i <= 100) return 95;
	else printf("wrong");
	return -1;
}
int a[100000];
int main(){
	int n = 0;
	while(scanf("%d", &a[n]) != EOF){
#ifdef HUNDRED
		printf("%d ", a[n]);
#endif
#ifdef APLUS
		Print_rank(a[n]);
#endif
		n++;
	}
#ifdef APLUS
	double ave_rank = 0;
	double ave_score = 0;
	for(int i = 0; i < n; i++){
		ave_rank += Search_rank(a[i]);
		ave_score += Search_score(a[i]);
	}
	ave_rank /= (double) n;
	ave_score /= (double) n;
	printf("%.1lf %.1lf\n", ave_rank, ave_score);
#endif
#ifdef HUNDRED
	int sum = 0;
	for(int i = 0; i < n; i++){
		sum += a[i];
	}
	double ave = (double)sum / (double)n;
	printf("%.1lf\n", ave);
#endif
}