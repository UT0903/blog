#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char name[16];
    int numComponent;
    int componentPartList[64];
    int price;
}ComponentPart;

int cmp( const void *a, const void *b)
{
	return( strcmp((char *)a,(char *)b) );
}

int Find(int search, ComponentPart list[], int i){
	if(list[search].price == 0){
		int sum = 0;
		for(int j = 0; j < list[search].numComponent; j++){
			sum += Find(list[search].componentPartList[j], list, search);
		}
		return sum;
		
	}
	return list[search].price;
}

void findPrice(int N, ComponentPart list[]){
	for(int i = 0; i < N; i++){
		if(list[i].numComponent != 0){
			for(int j = 0; j < list[i].numComponent; j++){
				//printf("list[i].componentPartList[j] = %d\n", list[i].componentPartList[j]);
				list[i].price += Find(list[i].componentPartList[j], list, i);
				//printf("list[%d].price = %d\n", i, list[i].price);
			}
		}
	}
	qsort(list, N, sizeof(ComponentPart), cmp);
	for(int i = 0; i < N; i++){
		printf("%s %d\n", list[i].name, list[i].price);
	}

}

#include<stdio.h>
//#include"componentPart.h"
int main(){
    int N;
    scanf("%d",&N);
    ComponentPart list[N];
    for(int i=0;i<N;i++){
        scanf("%s%d",list[i].name,&list[i].numComponent);
        if(list[i].numComponent){
            for(int j=0;j<list[i].numComponent;j++)
                scanf("%d",&list[i].componentPartList[j]);
            list[i].price=0;
        }
        else
            scanf("%d",&list[i].price);
    }
    findPrice(N,list);
    return 0;
}