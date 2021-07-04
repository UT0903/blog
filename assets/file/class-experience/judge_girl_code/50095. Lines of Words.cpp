# include <stdio.h>
# include <string.h>

int length;
char none;
char **flptr[1025], *slptr[1025*1025];
char string[10000000];
int string_length[1024];
int main(){
	scanf("%d", &length);
	scanf("%c", &none);
	int i;
	int ptr = 0;
	char last;
	int j = 0;
	for(i = 0; i < length; i++){
		flptr[i] = &slptr[j];
		while(1){
		scanf("%s%c", &string[ptr], &last);
		slptr[j]= &string[ptr];
		string_length[i]++;
		//printf("strlen(&string[%d]) = %d\n", ptr, strlen(&string[ptr]));
		ptr += strlen(&string[ptr]) + 1;
		//printf("ptr = %d\n", ptr);
		j++;
		if(last == '\n') break;
		//	printf("slptr[%d][%d] = %p\n", i, j, &slptr[i][j]);
			//printf("OK\n");
		}
		
		//printf("flptr[%d] = %s\n", i, *flptr[i]);
	}
	/*for(i = 0; i < 3; i++){
		for(int j = 0; slptr[i][j] != NULL; j++){
			printf("slptr[%d][%d] = %p\n", i, j, &slptr[i][j]);
		}
		
	}*/
	int od, a1, a2, b1, b2;
	char *temp;
	scanf("%d", &od);
	for(i = 0; i < od; i++){
		scanf("%d %d %d %d", &a1, &a2, &b1, &b2);
		temp = flptr[a1][a2];
		flptr[a1][a2] = flptr[b1][b2];
		flptr[b1][b2] = temp;
	}
	
	
	int x = 0, y = 0;
	for(x = 0;x < length; x++){
		for(y = 0; y < string_length[x]; y++){
			printf("%s%s", *flptr[x], (y == string_length[x] - 1)? "\n" : " ");
			*(flptr[x]++);
		}
	}
	
	
	
	
} 
