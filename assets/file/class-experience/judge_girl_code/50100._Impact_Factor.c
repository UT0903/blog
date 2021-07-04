#include <stdio.h>
#define MAXP 1024
//#include "compute.h"
#include <stdlib.h>
#include <string.h>

int end = 0;
typedef struct {
    char journalName[64];
    int numCitedPaper;
    int citedPaperIndex[1024];
} paper;
typedef struct {
    char Name[64];
    int fircnt;
    int seccnt;
} fuck;
fuck super[MAXP] = {};
int Find(char *name){
    for(int i = 0; i < end; i++){
        if(strcmp(name, super[i].Name) == 0){
            //printf("i = %d\n", i);
            return i;
        }
    }
    //printf("no\n");
    return -1;
}

int compare( const void *a, const void *b)
{
return( strcmp((char *)a,(char *)b) );
}

void compute(paper P[], int N){
    
    for(int i = 0; i < N; i++){
        if(Find(P[i].journalName) == -1){
            strcpy(super[end].Name, P[i].journalName);
            //printf("super[%d].Name = %s\n", i, super[end].Name);
            super[end].seccnt++;
            end++;
            
        }

        else{
            super[Find(P[i].journalName)].seccnt++;
           // printf("OK2\n");
        }
    }
    //printf("OK3\n");
    for(int i = 0; i < N; i++){
        for(int j = 0; j < P[i].numCitedPaper; j++){
            int dd = P[i].citedPaperIndex[j];
            super[Find(P[dd].journalName)].fircnt++;
        }
    }
    //printf("OK4\n");
    qsort(super, end, sizeof(fuck), compare);
    for(int i = 0; i < end; i++){
        printf("%s %d/%d\n", super[i].Name, super[i].fircnt, super[i].seccnt);
    }
}


int main() {
    int N;
    paper P[MAXP] = {};
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s%d", P[i].journalName, &P[i].numCitedPaper);
        for (int j = 0; j < P[i].numCitedPaper; j++)
            scanf("%d", &P[i].citedPaperIndex[j]);
    }
    compute(P, N);
    return 0;
}