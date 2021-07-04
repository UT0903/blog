#include <stdio.h>
long long int D, a, b, c, A, B, C;
int solved = 0; 
void dfs(long long int a, long long int b, long long int c, long long int d) {
    if (d < 0) return;
    if (!solved && d == 0) {
        solved = 1;
        return;   
    }
    int dir[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
    int i;
	for (i = 0; i < 3 && !solved; i++) {
        if (a - dir[i][0] >= 0 && b - dir[i][1] >= 0 && c - dir[i][2] >= 0) {
              dfs(a - dir[i][0], b - dir[i][1], c - dir[i][2], d - A*dir[i][0] - B*dir[i][1] - C*dir[i][2]);
        }
    }
    return;
}
int judge(long long int a, long long int b, long long int c, long long int D) {
    solved = 0;
    dfs(a, b, c, D);
    return solved;
}
int main(){
    int n;
    scanf("%d",&n);
    while(n--){
        scanf("%lld%lld%lld%lld%lld%lld%lld", &D, &a, &b, &c, &A, &B, &C);
        if (judge(a,b,c,D)) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}
