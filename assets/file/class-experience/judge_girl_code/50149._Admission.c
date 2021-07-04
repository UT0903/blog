#include <stdio.h>
#include <stdlib.h>
#define MAXN 20010
typedef struct{
	int ID, a, b, c, d, e, total;
}Subject;
Subject subject[MAXN];
int cmp(void *dataa1, void *dataa2){
	Subject *data1 = (Subject *) dataa1;
	Subject *data2 = (Subject *) dataa2;
	if(data1->total < data2->total) return 1;
	else if(data1->total > data2->total) return -1;
	else if(data1->a < data2->a) return 1;
	else if(data1->a > data2->a) return -1;
	else if(data1->b < data2->b) return 1;
	else if(data1->b > data2->b) return -1;
	else if(data1->c < data2->c) return 1;
	else if(data1->c > data2->c) return -1;
	else if(data1->d < data2->d) return 1;
	else if(data1->d > data2->d) return -1;
	else if(data1->e < data2->e) return 1;
	else if(data1->e > data2->e) return -1;
	else return 0;
}
int Issame(Subject x, Subject y){
	//printf("%d %d %d %d %d %d\n", x.ID, x.a, x.b, x.c, x.d, x.e);
	//printf("%d %d %d %d %d %d\n", y.ID, y.a, y.b, y.c, y.d, y.e);
	return (x.a == y.a && x.b == y.b && x.c == y.c && x.d == y.d && x.e == y.e);
}
int main(){
	int N, M;
	scanf("%d %d", &M, &N);
	for(int i = 0; i < N; i++){
		scanf("%d %d %d %d %d %d", &subject[i].ID, &subject[i].d, &subject[i].b, &subject[i].a, &subject[i].c, &subject[i].e);
		subject[i].total = subject[i].a + subject[i].b + subject[i].c + subject[i].d + subject[i].e;
	}
	qsort(subject, N, sizeof(Subject), cmp);
	/*printf("\n");
	for(int i = 0; i < N; i++){
		printf("%d %d %d %d %d %d\n", subject[i].ID, subject[i].a, subject[i].b, subject[i].c, subject[i].d, subject[i].e);
	}*/
	int i;
	for(i = 0; i < M; i++){
		printf("%d\n", subject[i].ID);
	}
	while(Issame(subject[i - 1], subject[i]) && i < N){
		printf("%d\n", subject[i].ID);
		i++;
	}

}