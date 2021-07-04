#include <stdio.h>
//#include "heap.h"
#define MAXHEAP 100
struct Heap{
    int ary[MAXHEAP];
    int num;
};
void initialize(struct Heap *heap){
	heap->num = 0;
}
int removeMin(struct Heap *heap){
	int min = 10000000, min_num = -1;
	for(int i = 0; i < heap->num; i++){
		if(heap->ary[i] < min){
			min = heap->ary[i];
			min_num = i;
		}
	}
	for(int i = (min_num + 1); i < heap->num; i++){
		heap->ary[i - 1] = heap->ary[i];
	}
	heap->num--;
	return min;
}
void add(struct Heap *heap, int i){
	if(heap->num >= MAXHEAP) return;
	heap->ary[heap->num] = i;
	heap->num++;
}
int isFull(struct Heap *heap){
	if(heap->num >= MAXHEAP) return 1;
	else return 0;
}
int isEmpty(struct Heap *heap){
	if(heap->num <= 0) return 1;
	else return 0;
}
void Print(struct Heap *heap){
	printf("-----------\n");
	for(int i = 0; i < heap->num; i++){
		printf("heap->ary[%d] = %d\n",i ,heap->ary[i]);
	}
}

int main(){
	struct Heap myheap;
	initialize(&myheap);
	printf("empty = %d\n", isEmpty(&myheap));
	Print(&myheap);
	add(&myheap, 1);
	Print(&myheap);
	add(&myheap, 3);
	add(&myheap, 5);
	add(&myheap, 2);
	add(&myheap, 4);
	Print(&myheap);
	printf("full = %d\n", isFull(&myheap));
	removeMin(&myheap);
	Print(&myheap);

}