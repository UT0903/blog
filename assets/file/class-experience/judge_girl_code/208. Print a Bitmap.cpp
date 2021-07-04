# include <stdio.h>
int print[100000];
int main(){
	int w, l, j = 0, i;
	unsigned int a;
	char one[2], zero[2];
	scanf("%d %d", &w, &l);
	scanf("%s %s", one, zero);
	//printf("%c, %c", one[0] , zero[0]);
	while(scanf("%u", &a) != EOF){
		for(i = 0; i < 32; i++){
			print[31 - i + j * 32] = a & 1;
			a = a >> 1;
		}
		j++;
	}
	for(i = 0; i < w * l; i++){
		if(print[i] == 0){
			printf("%c%s", zero[0], (i % w == w - 1)? "\n":"");
		}
		else{
			printf("%c%s", one[0], (i % w == w - 1)? "\n":"");
		}
		
	}
}
