#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main()
{
    char S[1024]; // initial string
    char ins[1007]; // instruction
    char de[2]; // delimiter
 
    char A[501];
    char B[501];
 
    scanf("%s", S);
 
    while (scanf("%s", ins) != EOF) {
        if (strlen(ins) == 1 && ins[0] == 'p'){
            printf("%s\n", S);
            continue;
        }       
        strncpy(de, &ins[1], 1);
        de[1] = '\0';
        char *ptr = strtok(&ins[1], de);
        for(int i = 0; i < 2 && ptr != NULL; i++) {
            if (i) strcpy(B, ptr);
            else strcpy(A, ptr);
            ptr = strtok(NULL, de);
        }
        printf("A = %s, B =  %s", A, B);
        if (strcmp(A, B) == 0) continue;
    ptr = strstr(S, A);
    if (ptr != NULL) {
            if (strlen(A) == strlen(B)){
                strncpy(ptr, B, strlen(B));
            } else{
                strcpy(ptr+strlen(B), ptr+strlen(A));
                strncpy(ptr, B, strlen(B));
            }
        }
    }
    return 0;
}
