#include <stdio.h>
#include <stdlib.h>
//#include "loops.h"
# define MAXN 1000000
 
int print_max = 0, print_min = MAXN, len_max = 0, len_min = MAXN, longe = 0, shor = 0; 
int len[MAXN], fin[MAXN];
int maxi[MAXN], mini[MAXN];
//*A, *B[]
void loops(int N, int A[], int *B[], int ans[4]){
    int temp, max, min;
    int i = 0, k, j = 0, x, start;
    for(start = 0; start < N; start++){
        if(fin[start] == 1) continue;
		//printf("N = %d\n", N);
        i = start;
        temp = *B[i];
        fin[i] = 1;
        int count = 1;
        //printf("temp = %d\n", temp);
            max = *B[i];
            min = *B[i];
            i = B[i] - A;
        while(*B[i] != temp){
            count++;
            fin[i] = 1;
            if(max < *B[i]){
                max = *B[i];
            }
            if(min > *B[i]){
                min = *B[i];
            }
            i = B[i] - A;
            //printf("OK\n");
        }
        //printf("count = %d\n", count);
        len[j] = count;
        maxi[j] = max;
        mini[j] = min;
        j++;
    }
    
    int y;
    for(y = 0; y < j; y++){
        if(len[y] > len_max){
        	len_max = len[y];
			longe = y;
		}
		else if(len[y] == len_max){
            if(maxi[y] > maxi[longe]){
            	longe = y;
			}
        }
        if(len[y] < len_min){
            len_min = len[y];
            shor = y;
        }
        else if(len[y] == len_min){
        	if(mini[y] < mini[shor]){
            	shor = y;
			}
		}
 
 
 
        /*printf("len[%d] = %d\n", y, len[y]);
        printf("maxi[%d] = %d\n", y, maxi[y]);
        printf("mini[%d] = %d\n", y, mini[y]);*/
    }
    ans[0] = len_max;
    ans[1] = len_min;
    ans[2] = maxi[longe];
    ans[3] = mini[shor];
    //printf("%d\n%d\n%d\n%d\n", len_max, len_min, print_max, print_min);
 
}



#include <stdio.h>
#include <stdlib.h>
//#include "loops.h"
#define MAXN 1000000
int main(){
    int N;
    int *A = (int *)malloc(sizeof(int) * MAXN);
    int **B = (int **)malloc(sizeof(int *) * MAXN);
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
        scanf("%d", A + i);
    for(int i = 0, ptr; i < N; i++){
        scanf("%d", &ptr);
        B[i] = A + ptr;
    }
    int ans[4];
    loops(N, A, B, ans);
    for(int i = 0; i < 4; i++)
        printf("%d\n", ans[i]);
    return 0;
}
