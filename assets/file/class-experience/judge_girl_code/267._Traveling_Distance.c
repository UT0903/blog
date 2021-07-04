#include <stdio.h>
#include <stdlib.h>
typedef struct point{
	int x;
	int y;
}Point;
Point cities[100000];
int square(int x){
	return x * x;
}
int compare(const void *data1, const void *data2){
	Point *tmp1 = (Point *) data1;
	Point *tmp2 = (Point *) data2;
	if(square(tmp1->x) + square(tmp1->y) < square(tmp2->x) + square(tmp2->y)) return -1;
	else if(square(tmp1->x) + square(tmp1->y) > square(tmp2->x) + square(tmp2->y)) return 1;
	else if(tmp1->x < tmp2->x) return -1;
	else if(tmp1->x > tmp2->x) return 1;
	else if(tmp1->y < tmp2->y) return -1;
	else if(tmp1->y > tmp2->y) return 1;
	else return 0;
}

int Distance_count(Point cities[], int n){
	int sum = square(cities[0].x) + square(cities[0].y);
	for(int i = 1;i < n; i++){
		sum += (square(cities[i - 1].x - cities[i].x) + square(cities[i - 1].y - cities[i].y));
	}
	return sum;
}
int main(){
	int i = 0;
	while(scanf("%d %d", &cities[i].x, &cities[i].y) != EOF) i++;
	qsort(cities, i, sizeof(Point), compare);
#ifdef DEBUG
	printf("----------------\n");
	for(int j = 0; j < i; j++){
		printf("x = %d, y = %d\n", cities[j].x, cities[j].y);
	}
#endif
	printf("%d\n", Distance_count(cities, i));
}