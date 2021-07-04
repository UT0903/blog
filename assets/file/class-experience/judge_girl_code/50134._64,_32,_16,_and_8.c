#include <stdio.h>
#include <string.h>
/*unsigned long long int ULLI;
scanf("%llu", &ULLI);
printf("%llu", ULLI);
unsigned int UI;
scanf("%u", &UI);
printf("%u", UI);
unsigned short US;
scanf("%hu", &US);
printf("%hu", US);*/
unsigned long long poww(int x, int time){
	unsigned long long now = 1;
	for(int i = 0; i < time; i++){
		now *= x;
	}
	return now;
}
int main(){
	int type;
	scanf("%d", &type);
	if(type == 0){
		char format[5];
		while(scanf("%s", format) != EOF){
			unsigned int UI;
			unsigned long long int ULLI = 0;
			unsigned short US;
			char input[3];
			scanf("%u %hu %s", &UI, &US, input);
			int k = 0;
			//printf("US = %hu\n", US);
			for(int i = 0; i < 4; i++){
				if(format[i] == 'L'){
					if(i != 0){
						ULLI = ULLI << 32;
					}
					ULLI += UI;
					//printf("L = %llu\n", ULLI);
					
				}
				else if(format[i] == 'S'){
					if(i != 0){
						ULLI = ULLI << 16;
					}
					ULLI += US;
					//printf("S = %llu\n", ULLI);
					
				}
				else if(format[i] == 'C'){
					if(i != 0) ULLI = ULLI << 8;
					ULLI += input[k++];
					//printf("C = %llu\n", ULLI);
					
				}
			}
			printf("%llu\n", ULLI);
		}
	}
	else{
		char format[5];
		while(scanf("%s", format) != EOF){
			unsigned int UI;
			unsigned long long int ULLI;
			unsigned short US;
			char input[3];
			input[2] = '\0';
			scanf("%llu", &ULLI);
			int k = 1;
			for(int i = 3; i >= 0; i--){
				if(format[i] == 'L'){
					UI = ULLI % poww(2, 32);
					ULLI = ULLI >> 32;
				}
				else if(format[i] == 'S'){
					US = ULLI % poww(2, 16);
					ULLI = ULLI >> 16;
				}
				else if(format[i] == 'C'){
					input[k--] = ULLI % poww(2, 8);
					ULLI = ULLI >> 8;
				}
			}
			printf("%u %hu %s\n", UI, US, input);
		}
	}
}