#include <stdio.h>
int mati[3][3] = {};
int try(int a,int b, int c){
	//printf("a = %d, b = %d, c = %d\n", a, b, c);
	if(a < 0 || b < 0 || c < 0) return 0;
	if(a == 0 && b == 0 && c == 0) return 1;
	if(a > 0 && b > 0 && c > 0){
		if(try(a - mati[0][0], b - mati[1][0], c - mati[2][0]))
			return 1;
		if(try(a - mati[0][1], b - mati[1][1], c - mati[2][1]))
			return 1;
		if(try(a - mati[0][2], b - mati[1][2], c - mati[2][2]))
			return 1;
		return 0;
	}
	return 0;
}
void scany(int x, int y){
	if(y == 3) {
		return;
	}
	scanf("%d", &mati[y][x]);
	return scany(x, y + 1);
}
void scanx(int x,int y){
	if(x == 3) return;
	scany(x, y);
	y = 0;
	return scanx(x + 1, y);
}
void scan(int n){
	if(n == 0) return;
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	if(try(a, b, c)) printf("yes\n");
	else{
		printf("no\n");
	}
	return scan(n - 1);
} 
int main(){
	scanx(0, 0);
	int n;
	scanf("%d", &n);
	scan(n);
}
