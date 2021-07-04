#include <stdio.h>
int hasEOF = 0;
int readchar() {
    static int N = 1<<20;
    static char buf[1<<20];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) {
            hasEOF = 1;
            return EOF;    
        }
        p = buf;
    }
    return *p++;
}
int ReadInt(int *x) {
    char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int bookshelf[10];
int main() {
    int x, i, j;
    while (ReadInt(&x)) {
    	int in = 0;
		for(i = 0; i < 8; i++){
    		if(bookshelf[i] == x){
    			in = 1;
    			break;
			}
		}
		if(in){
			for(j = i; j < 7; j++){
				bookshelf[j] = bookshelf[j+1];
			}
			bookshelf[7] = x;
        	
		}
		else{
			for(j = 0; j < 7; j++){
				bookshelf[j] = bookshelf[j+1];
			}
			bookshelf[7] = x;
		}
		
    }    
    for(i = 0; i < 8; i++){
    	printf("%d%s", bookshelf[i], (i == 7)? "\n" : " ");
	}
    return 0;
}
