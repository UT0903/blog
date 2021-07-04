#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct{
	char lastname[80];
	char firstname[80];
	char ID[80];
	int salary;
	int age;
} Data;

Data data[50];

int Findword(char temp[][100], int k, char* word){
	for(int i = 0; i < k; i++){
		if(strcmp(temp[i], word) == 0){
			return i;
		}
	}
	return -1;
}
int Findfield(char* in){
	char* cmp[5] = {"lastname", "firstname", "ID", "salary", "age"};
	for(int i = 0; i < 5; i++){
		if(strcmp(cmp[i], in) == 0){
			return i;
		}
	}
	return -1;
}
int Findop(char* in){
	char* cmp[4] = {"==", "!=", ">", "<"};
	for(int i = 0; i < 4; i++){
		if(strcmp(cmp[i], in) == 0){
			return i;
		}
	}
	return -1;
}


int N, M;
char temp[30][100], input[300];
int ok[50] = {0};
int main(){
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		scanf("%s%s%s%d%d", data[i].lastname, data[i].firstname, data[i].ID, &data[i].salary, &data[i].age);
	}
	scanf("%d", &M);
	for(int i = 0; i < M; i++){
		int k = 0;
		char _a;
		while(scanf("%s%c", temp[k], &_a) != EOF && _a != '\n'){
			k++;
		}
		//printf("OK\n");
		//int j = Findword(temp, k, "where");
		int j;
		for(int i = 0; i < k; i++){
			if(strcmp(temp[i], "where") == 0){
				j = i;
			}
		}
		int sub;// = Findfield(temp[j + 1]);
		char* cmp[5] = {"lastname", "firstname", "ID", "salary", "age"};
		for(int i = 0; i < 5; i++){
			if(strcmp(cmp[i], temp[j + 1]) == 0){
				sub = i;
			}
		}

		int op;// = Findop(temp[j + 2]);
		char* cmp1[4] = {"==", "!=", ">", "<"};
		for(int i = 0; i < 4; i++){
			if(strcmp(cmp1[i], temp[j + 2]) == 0){
				op = i;
			}
		}
		//for(int x = 0; x < N; x++){
			if(sub == 0){
				if(op == 0){
					for(int y = 0; y < N; y++){
						if(strcmp(temp[j + 3], data[y].lastname) == 0){
							ok[y] = 1;
							//printf("data[%d].lastname = %s\n", y, data[y].lastname);
						}
					}
				}
				else if(op == 1){
					for(int y = 0; y < N; y++){
						if(strcmp(temp[j + 3], data[y].lastname) != 0){
							ok[y] = 1;
						}
					}
				}
			}
			else if(sub == 1){
				if(op == 0){
					for(int y = 0; y < N; y++){
						if(strcmp(temp[j + 3], data[y].firstname) == 0){
							ok[y] = 1;
						}
					}
				}
				else if(op == 1){
					for(int y = 0; y < N; y++){
						if(strcmp(temp[j + 3], data[y].firstname) != 0){
							ok[y] = 1;
						}
					}
				}
			}
			else if(sub == 2){
				if(op == 0){
					for(int y = 0; y < N; y++){
						if(strcmp(temp[j + 3], data[y].ID) == 0){
							ok[y] = 1;
						}
					}
				}
				else if(op == 1){
					for(int y = 0; y < N; y++){
						if(strcmp(temp[j + 3], data[y].ID) != 0){
							ok[y] = 1;
						}
					}
				}
			}
			else if(sub == 3){
				if(op == 0){
					for(int y = 0; y < N; y++){
						if(data[y].salary == atoi(temp[j+3])){
							ok[y] = 1;
						}
					}
				}
				else if(op == 2){
					for(int y = 0; y < N; y++){
						if(data[y].salary > atoi(temp[j+3])){
							ok[y] = 1;
						}
					}
				}
				else if(op == 3){
					for(int y = 0; y < N; y++){
						if(data[y].salary < atoi(temp[j+3])){
							ok[y] = 1;
						}
					}
				}
			}
			else if(sub == 4){
				if(op == 0){
					for(int y = 0; y < N; y++){
						if(data[y].age == atoi(temp[j+3])){
							ok[y] = 1;
						}
					}
				}
				else if(op == 2){
					for(int y = 0; y < N; y++){
						if(data[y].age > atoi(temp[j+3])){
							ok[y] = 1;
						}
					}
				}
				else if(op == 3){
					for(int y = 0; y < N; y++){
						if(data[y].age < atoi(temp[j+3])){
							ok[y] = 1;
						}
					}
				}
			}
		//}
		for(int count = 0; count < N; count++){
			if(ok[count]){
				for(int count1 = 1; count1 < j; count1++){
					if(strcmp(temp[count1], "lastname") == 0){
						printf("%s", data[count].lastname);
					}
					else if(strcmp(temp[count1], "firstname") == 0){
						printf("%s", data[count].firstname);
					}
					else if(strcmp(temp[count1], "ID") == 0){
						printf("%s", data[count].ID);
					}
					else if(strcmp(temp[count1], "salary") == 0){
						printf("%d", data[count].salary);
					}
					else if(strcmp(temp[count1], "age") == 0){
						printf("%d", data[count].age);
					}
					printf("%s", (count1 == j - 1)? "\n" : " ");
				}
			}
		}
		for(int fuck = 0; fuck < N; fuck++){
			ok[fuck] = 0;
		}
		
	}
}