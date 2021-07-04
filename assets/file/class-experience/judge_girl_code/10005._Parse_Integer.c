#include <stdio.h> 
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MX 100000000

char buf[MX];
char output[MX];
char temp[1001];
int main(){
    int c = fread(buf, 1, MX, stdin);
    int i = 0, op = 0;
    //printf("c = %d\n", c);
    while(i < c){
        if(isdigit(buf[i])){
            int k = 0;
            while(isdigit(buf[i])){
                temp[k++] = buf[i++];
            }

            int count = 0;
            for(int x = 0; x < k; x++){
                //printf("%c", temp[x]);
                if(temp[x] == '0') count++;
            }
            //printf("\n");
            if(k == count){
                output[op++] = '0';
                output[op++] = '\n';
            }
            else{
                for(int j = 0; j < k; j++){
                    output[op++] = temp[j];
                }
                output[op++] = '\n';
            }
        }
        i++;
    }
    fwrite(output, 1, op, stdout);
}