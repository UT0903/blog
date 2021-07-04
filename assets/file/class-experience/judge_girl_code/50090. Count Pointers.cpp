# include <stdio.h>

/*void Find(int *a, int *addr[512], int count[512]){
	int j, fin = 0;
	for(j = 0; addr[j] != 0; j++){
		if(*a == addr[j]){
			count[j]++;
			fin = 1;
			break;
		}
	}
	if(fin == 0){
		addr[j] = *a;
		count[j] = 1;
	}
}*/

void count(int **p[]){
	int count[512] = {0}, *addr[512] = {0};
	int i;
	for(i = 0; p[i] != NULL; i++){
		//Find(p[i], addr, count);
		
		int j, fin = 0;
		for(j = 0; addr[j] != 0; j++){
			if(*p[i] == addr[j]){
				count[j]++;
				fin = 1;
				break;
			}
		}
		if(fin == 0){
			addr[j] = *p[i];
			count[j] = 1;
		}	
	}
	
	int x, y, *temp, tem;
	for(x = 0; count[x] != 0; x++){
		for(y = 0; count[y] != 0; y++){
			if(count[y] > count[y + 1] && count[y + 1] != 0){
				temp = addr[y];
				addr[y] = addr[y+1];
				addr[y+1] = temp;
				tem = count[y];
				count[y] = count[y + 1];
				count[y + 1] = tem;
				
			}
			else if(count[y] == count[y + 1] && count[y + 1] != 0 && *addr[y] > *addr[y + 1]){
				temp = addr[y];
				addr[y] = addr[y+1];
				addr[y+1] = temp;
				tem = count[y];
				count[y] = count[y + 1];
				count[y + 1] = tem;
			}
		}
	}
	for(i = 0; addr[i] != 0; i++){
		printf("%d %d\n", *addr[i], count[i]);
	}
	
}



#include <stdio.h>
//#include "count.h"
 
#define MAX_SIZE_PTRARRAY 512
#define MAX_NUM_PTR 512
#define MAX_NUM_INTVAR 512
 
int main(){
  int **ptrArray[MAX_SIZE_PTRARRAY] = {};
  int  *intPtr[MAX_NUM_PTR];
  int   intVar[MAX_NUM_INTVAR];
 
  intVar[0] = 7;
  intVar[1] = 7;
  intVar[2] = 6;
  ptrArray[0] = &intPtr[0];
  ptrArray[1] = &intPtr[1];
  ptrArray[2] = &intPtr[2];
  ptrArray[3] = &intPtr[2];
  ptrArray[4] = &intPtr[3];
  ptrArray[5] = &intPtr[4];
  ptrArray[6] = NULL;
  intPtr[0] = &intVar[0];
  intPtr[1] = &intVar[1];
  intPtr[2] = &intVar[2];
  intPtr[3] = &intVar[2];
  intPtr[4] = &intVar[1];
 
  count(ptrArray);
 
  return 0;
}
