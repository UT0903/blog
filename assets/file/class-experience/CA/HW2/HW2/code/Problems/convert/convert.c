#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 15

int convert(char *);

int main()
{
    char input[SIZE];
    int out;

    while (scanf("%s", input) != EOF) {
        out = convert(input);
	printf("%d\n", out);
    }

    return 0;
}

int convert(char *str){
	int minus = 0, i = 0, sum = 0;
	if(str[i] == '+'){
		i++;
	}
	else if(str[i] == '-'){
		minus = 1;
		i++;
	}

	while(str[i] != '\0'){
		if(!isdigit(str[i])){
			return -1;
		}
		sum *= 10;
		sum += str[i] - '0';

		i++;
	}
	if(minus != 0) sum = -sum;
	return sum;
}