# include <stdio.h>
int dx[2] = {0, 1}, dy[2] = {1, 0}, r, c, count; 
void fuck(int x, int y){
	if(x == r - 1 && y == c - 1){
		count++;
		return;
	}
	if(x == r || y == c){
		return;
	}
	for(int i = 0; i < 2; i++){
		fuck(x + dx[i], y + dy[i]);
	}
	return;
}
int main(){
	scanf("%d%d", &r, &c);
	fuck(0, 0);
	printf("%d\n", count);
}