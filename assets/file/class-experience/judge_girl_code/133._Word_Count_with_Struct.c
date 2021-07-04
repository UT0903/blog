#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct string_count {
        char seen[80];
        int count;
};
typedef struct string_count String;
int num = 0, amount = 0;
int compare_and_add(char *string, struct string_count strings[]) {
        for(int i = 0; i < num; i++){
                if(strcmp(string, strings[i].seen) == 0){
                        strings[i].count++;
                        amount++;
                        //printf("OK\n");
                        return 1;
                }
        }
        strcpy(strings[num].seen,string);
        strings[num].count++;
        amount++;
        num++;
        
        return 0;
        
}
int compare(const void *data1, const void *data2){
        String *tmp1 = (String *)data1;
        String *tmp2 = (String *)data2;
        if(tmp1->count < tmp2->count) return -1;
        else if(tmp1->count > tmp2->count) return 1;
        else{
                //printf("check = %d\n", strcmp(((String *)data1)->seen, ((String *)data2)->seen));
                return strcmp(tmp1->seen, tmp2->seen);
        }
}
void sort(struct string_count strings[]) {
        //printf("num1 = %d\n", num);
        qsort(strings, num, sizeof(String), compare);
}
void print(struct string_count strings[]) {
        //printf("num = %d\n", num);
        for(int i = 0; i < num; i++){
                printf("%d %s\n", strings[i].count, strings[i].seen);
        }
}

int main() {
        struct string_count strings[20];
        int i;
        for( i=0 ; i<20 ; i++ )
                strings[i].count = 0;
        compare_and_add( "This", strings );
        compare_and_add( "is", strings );
        compare_and_add( "an", strings );
        compare_and_add( "apple,", strings );
        compare_and_add( "and", strings );
        compare_and_add( "this", strings );
        compare_and_add( "is", strings );
        compare_and_add( "a", strings );
        compare_and_add( "book.", strings );
        sort( strings );
        print( strings );
        return 0;
}