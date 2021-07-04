# include <stdio.h>
 
int validMoveNum(int r, int c, int n, int visited[100][100]){
	int move[8][2] = {{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
	if(visited[r][c] == 1 || r >= n || r < 0 || c >= n || c < 0){
		return -1;
	}
	else{
		int count;
		count = 0;
	    for(int j=0; j<8; j++){
			if(r + move[j][0] < n && r + move[j][0] >= 0 && c + move[j][1] < n && c + move[j][1] >= 0 && visited[r + move[j][0]][c + move[j][1]] == 0){
				count++;
			}	
		}
		return count;
	}
} 

int nextMove(int r, int c, int n, int visited[100][100]){
	int p[8] = {0}, min = 10, best = -1;
	int move[8][2] = {{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
	//for(int i=0; i<m; i++){ //each knight
        for(int j=0; j<8; j++){
            p[j] = validMoveNum(r+move[j][0], c+move[j][1], n, visited);
			if(p[j] != -1 && p[j] < min){
        		min = p[j];
        		best = j;
			}
		}
		return best;
    //}
}

#include <stdio.h>
//#include "nextMove.h"
//#include "validMoveNum.h"
#define MAXN 100
int r[MAXN*MAXN];
int c[MAXN*MAXN];
int map[MAXN][MAXN] = {0};
int visited[MAXN][MAXN]={0};
int move[8][2] = {{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
int main(){
	int stop[100] = {0};
	int n,m, best;
    scanf("%d%d", &n, &m);
    for(int i=0; i<m; i++){
        scanf("%d%d", &r[i], &c[i]);
        visited[r[i]][c[i]] = 1;
        map[r[i]][c[i]] = (i+1) * 10000;
    }
    int last[100] = {0}, fin = 0;
    
    while(!fin){
    	int i;
	    for(i=0; i<m; i++){
	    	best = nextMove(r[i], c[i], n, visited);
	    	if(best == -1) stop[i] = 1;
	    	else{
	    		r[i] += move[best][0];
	    		c[i] += move[best][1];
	    		visited[r[i]][c[i]] = 1;
	    		last[i]++;
	    		map[r[i]][c[i]] = (i+1) *10000 + last[i];
			}
		}
		for(i = 0; i < m; i++){
			if(stop[i] == 0){
				fin = 0;
				break;
			}
			else fin = 1;
		}
	}
	int k, l;
	for(k = 0; k < n; k++){
		for(l = 0; l < n; l++){
			printf("%d%s", map[k][l], (l == n-1)? "" : " ");
		}
		printf("\n");
	}
}

