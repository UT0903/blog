#include <stdio.h>

int main(){
	int score, x;
	scanf("%d", &x);
	score = 0;
	if (x <= 0) score = score - 100;
	else {
		score = 0;
		if (x % 3 == 0) score = score + 3;
		if (x % 5 == 0) score = score + 5;
		if (x >= 100 && x <= 200) score = score + 50;
		else score = score - 50;
		}
	printf("%d", score);
}
