#include <stdio.h>
#include <string.h>
typedef struct{
  int id;
  char first_name[32];
  char last_name[32];
  int boss_id;
  int bosses[64];// = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  int bosses_num;
} Employee;

int N, M;
Employee employee[32];

int Find_num(char *fn, char *ln){
	for(int i = 0; i < N; i++){
		if(strcmp(fn, employee[i].first_name) == 0 && strcmp(ln, employee[i].last_name) == 0){
			return i;
		}
	}
	return -1;
}

int Find_num2(int find){
	for(int i = 0; i < N; i++){
		if(find == employee[i].id){
			return i;
		}
	}
	return -1;
}
void Build_Relationship(int num, int nochange){
	if(employee[num].id == employee[num].boss_id){
		employee[nochange].bosses[employee[nochange].bosses_num] = num;
		employee[nochange].bosses_num++;
		return;
	}
	//printf("OK\n");
	employee[nochange].bosses[employee[nochange].bosses_num] = num;
	employee[nochange].bosses_num++;
	Build_Relationship(Find_num2(employee[num].boss_id), nochange);
	return;
}
int Find_Relationship(int num, int cmp, int lbl){
	/*employee[lbl].bosses[employee[lbl].bosses_num] = num;
	employee[lbl].bosses_num++;*/
	if(employee[num].id == employee[cmp].id){
		return 1;
	}
	if(employee[num].id == employee[num].boss_id){
		return 0;
	}
	if(Find_Relationship(Find_num2(employee[num].boss_id), cmp, lbl)){
		return 1;
	}
	return 0;

}

int main(){
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		scanf("%d%s%s%d", &employee[i].id, employee[i].first_name, employee[i].last_name, &employee[i].boss_id);
	}
	scanf("%d", &M);

	for(int i = 0; i < N; i++){
		//printf("yes\n");
		Build_Relationship(Find_num2(employee[i].boss_id), i);
	}

	/*for(int i = 0; i < N; i++){
		for(int j = 0; j < employee[i].bosses_num; j++){
			printf("employee[%d].bosses[%d] = %d\n",i, j, employee[i].bosses[j]);
		}
		printf("OK\n");
	}*/
	
	for(int i = 0; i < M; i++){
		int num[2] = {0, 0};
		char a_fn[32], a_ln[32], b_fn[32], b_ln[32];
		scanf("%s%s%s%s", a_fn, a_ln, b_fn, b_ln);
		num[0] = Find_num(a_fn, a_ln);
		num[1] = Find_num(b_fn, b_ln);
		int rela[2] = {0, 0};
		rela[0] = Find_Relationship(num[0], num[1], num[0]);
		//printf("rela[0] = %d\n", rela[0]);
		rela[1] = Find_Relationship(num[1], num[0], num[1]);
		//printf("rela[1] = %d\n", rela[1]);
		if(rela[0] != 0){
			printf("subordinate\n");
		}
		else if(rela[1] != 0){
			printf("supervisor\n");
		}
		else if(rela[0] == 0 && rela[1] == 0){
			int yo = 0;
			for(int h = 0; h < employee[num[0]].bosses_num; h++){
				for(int r = 0; r < employee[num[1]].bosses_num; r++){
					if(employee[num[0]].bosses[h] == employee[num[1]].bosses[r]){
						printf("colleague\n");
						yo = 1;
						break;
					}
				}
				if(yo) break;
			}
			if(!yo)	printf("unrelated\n");
		}
		
		//printf("employee[%d].bosses_num = %d, employee[%d].bosses_num = %d\n", num[0], employee[num[0]].bosses_num, num[1], employee[num[1]].bosses_num);
		
	}
}