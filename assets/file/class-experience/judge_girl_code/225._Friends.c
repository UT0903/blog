#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

typedef struct person{
    unsigned int id;
    char name[32];
}Person;
typedef struct friends{
    unsigned id1;
    unsigned id2;
}Friends;
char name1[32], name2[32];
Person info[10000];
Friends rela[10000];
int P[1];
int F[1];
bool relationship[10000][10000];

int main(){
	FILE *fp;
	fp = fopen("friends", "rb");
	assert(fp != NULL);
	fread(P, sizeof(int), 1, fp);

	fread(info, sizeof(Person), P[0], fp);
	fread(F, sizeof(int), 1, fp);
	fread(rela, sizeof(Friends), F[0], fp);
	
	for(int i = 0; i < F[0]; i++){
		relationship[rela[i].id1][rela[i].id2] = 1;
		relationship[rela[i].id2][rela[i].id1] = 1;
	}

	while(scanf("%s %s", name1, name2) != EOF && strcmp(name1, "end") != 0){
		int p = 0, q = 0, id_1 = -1, id_2 = -1;
		for(int i = 0; i < P[0]; i++){

			if(strcmp(name1, info[i].name) == 0){
				p = 1;
				id_1 = info[i].id;
			}
			if(strcmp(name2, info[i].name) == 0){
				q = 1;
				id_2 = info[i].id;
			}
			if(p * q == 1){
				break;
			}
		}
		//printf("OK\n");
		if(relationship[id_1][id_2] == 1){
			printf("yes\n");
		}
		else printf("no\n");
	}
}