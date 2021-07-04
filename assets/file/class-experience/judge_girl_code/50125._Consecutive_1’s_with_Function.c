#include <stdio.h>
#define MAXN 256
int findLength (int array[][256], int N, int r, int c, int dr, int dc){
    int maxlen = 0;
    int len = 0;
    while(r < N && c < N && r >= 0 && c >= 0){
        if(array[r][c] == 1){
            len++;
        }
        else{
            len = 0;
        }
        if(len > maxlen){
            maxlen = len;
        }
        r+= dr;
        c+= dc;
    }
    return maxlen;
}
int main () {
    int array[MAXN][MAXN];
    int N, r, c;
    int direction[4][2] = {{1,0}, {1,1}, {0,1}, {-1,1}};
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &array[i][j]);
    int maxlen = 0, len;
    for (int i = 0; i < N; i++){
        for(int k = 0; k < 4; k++){
            len = findLength(array, N, 0, i, direction[k][0], direction[k][1]);
            if(maxlen < len) maxlen = len;
        }
    }
    for(int i = 0; i < N; i++){
        for(int k = 0; k < 4; k++){
            len = findLength(array, N, N-1, i, direction[k][0], direction[k][1]);
            if(maxlen < len) maxlen = len;
        }
    }
    for(int i = 0; i < N; i++){
        for(int k = 0; k < 4; k++){
            len = findLength(array, N, i, 0, direction[k][0], direction[k][1]);
            if(maxlen < len) maxlen = len;
        }
    }
    for(int i = 0; i < N; i++){
        for(int k = 0; k < 4; k++){
            len = findLength(array, N, i, N-1, direction[k][0], direction[k][1]);
            if(maxlen < len) maxlen = len;
        }
    }
    printf("%d\n", maxlen);
}