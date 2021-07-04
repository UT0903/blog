#include <stdio.h>

unsigned long long int fibonacci(int);

int main () {
    unsigned long long int ret;

    for (int i = 0; i < 94; i++) {
        ret = fibonacci(i);
        printf("%llu\n", ret);
    }

    return 0;
}

unsigned long long int fibonacci(int k){
	unsigned long long int a[100];
	a[0] = 0; a[1] = 1;
	for(int i = 0; i < 98; i++){
		a[i+2] = a[i+1] + a[i];
	}
	return a[k];
}