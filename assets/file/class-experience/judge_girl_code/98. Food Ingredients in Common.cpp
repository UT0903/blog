# include <stdio.h>
# include <string.h>

int Find(char food[][65], int n, char a[]){ // find the place where the food is
	int i, j;
	for(i = 0; i < 100; i++){
		if(strcmp(food[i], a) == 0){
			return i;
		}
	}
	return 0;
}


char food[100][65];
char ingre[100][11][65];
char a[65];
char b[65];
char print[11][65];
int main(){
	int n, i, g, x, test, j, k;
	scanf("%d", &n);
	for(i = 0; i < n; i++){                   // input
		scanf("%s", food[i]);
		scanf("%d", &x);
		for(j = 0; j < x; j++){
			scanf("%s", ingre[i][j]);
			//printf("ingre[%d][%d] = %s\n", i, j, ingre[i][j]);
		}
	}
	/*for(i = 0; i < n; i++){
		for(j = 0; ingre[i][j][0] !='\0'; j++){
			printf("%s ", ingre[i][j]);
		}
		printf("\n");
	}*/
	scanf("%d", &test);
	int num1, num2, l;
	for(g = 0; g < test; g++){
		memset(print, '\0', 11*65);
		scanf("%s %s", a, b);
		num1 = Find(food, n, a);
		num2 = Find(food, n, b);
		//printf("num1 = %d, num2 = %d\n",num1, num2);
		l = 0;
		for(i = 0; ingre[num2][i][0] != '\0' && i < 10; i++){            // compare the ingredients between two foods
			//printf("i = %d\n", i);
			for(j = 0; ingre[num1][j][0] != '\0' ; j++){
				if(strcmp(ingre[num1][j], ingre[num2][i]) == 0){
					//printf("i = %d, j = %d\n", i, j);
					strcpy(print[l], ingre[num1][j]);
					//printf("print[%d] = %s\n", l, print[l]);
					l++;
					break;
				}
			}
		}
		//printf("l = %d\n", l);
		if(l == 0){
			printf("nothing\n");
		}
		else{
			for(i = 0; i < l - 1; i++){
				for(j = 0; j < l - i - 1; j++){
					char temp[65];
					if(strcmp(print[j] , print[j+1]) > 0){  //bubble sort
						strcpy(temp, print[j]);
						strcpy(print[j], print[j+1]);
						strcpy(print[j+1], temp);
					}
					memset(temp, '\0', 65);
				}
			}
			
			for(i = 0; i < l; i++){
				printf("%s%s", print[i], (i == l - 1)? "\n":" ");
			}
		}
		
		
		
		
	}
}
