# include <stdio.h>
char a[1001];
int main(){
	int i = 0;
	int j;
	do{
		i = 0;
		scanf("%s", a);
	
		/*for(j = 0; a[j] != 10; j++){
			printf("%c ", a[j]);
		}
		printf("\n");*/
		if(a[0] == '-' && a[1] == '1') break;
		int three = 0, change = 0, ele1 = 0, ele2 = 0, five, even;
		while(a[i] > 47 && a[i] < 58){
			even = 0;
			if((a[i] - 48) % 2 == 0 ) even = 1;
			three = three + a[i] - 48;
			five = 0;
			if((a[i] - 48) % 5 == 0) five = 1;
			if(change % 2 == 0){
				ele1 = ele1 + a[i] - 48;
				change++;
			}
			else if(change % 2 == 1){
				ele2 = ele2 + a[i] - 48;
				change++;
			}
			//printf("%d %d %d %d %d\n", even, three, five, ele1, ele2);
			i++;
		}
		
			i = 0;
			for(j = 0; j < 1001; j++){
				a[j] = 0;
			}
			
			
			if(even == 1){
				printf("yes ");
			}
			else{
				printf("no ");
			}
			
			if(three % 3 == 0){
				printf("yes ");
			}
			else{
				printf("no ");
			}
			
			if(five == 1){
				printf("yes ");
			}
			else{
				printf("no ");
			}
			
			if((ele1 - ele2) % 11 == 0){
				printf("yes\n");
			}
			else{
				printf("no\n");
			}
			i++;
		
	}
	while(a[0] != '-' && a[1] != '1');
		
	
	
}
