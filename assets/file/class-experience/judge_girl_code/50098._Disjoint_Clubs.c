# include <stdio.h>
# include <string.h>
# include <stdlib.h>
int ans[101];
unsigned long long int group[101], cmp[64];
int group_num[101];
int N;

int Find(int K, int start, unsigned long long int temp){
    //printf("K = %d\n", K);
    if(K == 0){
        return 1;
    }
    else{
        for(int i = start; i < N; i++){
            if((group[i] & temp) == (unsigned long long)0) {
                //printf("i = %d\n", i);
                if(Find(K - 1, i, temp | group[i])){
                ans[K] = i;
                return 1;
                }
            }
        }
        //printf("NO\n");
        //temp = temp & (~group[start]);
        return 0;
    }
}
 
 


 
int main(){
    unsigned long long int pow = 1;
    for(int k = 0; k < 64; k++){
        cmp[k] = pow;
        pow *= 2;
        //printf("cmp[%d] = %llu\n", k, cmp[k]);
    }
    int K, num;
    scanf("%d %d", &N, &K);
    for(int i = 0; i < N; i++){
        scanf("%d", &num);
        for(int j = 0; j < num; j++){
            int digit;
            scanf("%d", &digit);
            //printf("digit = %d\n", digit);
            group[i] = (group[i] | cmp[digit]);
            //printf("group[%d] = %llu\n", i, group[i]);
        }
    }
    Find(K, 0, (unsigned long long)0);
    for(int i = K; i >= 1; i--){
        printf("%d\n", ans[i]);
    }
 
}