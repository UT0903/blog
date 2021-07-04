#include <stdio.h>
//#include "max.h"
 
int max(int *iptr[], int n){
	int i, max_ = -1000000;
	for(i = 0; i < n; i++){
		if(*iptr[i] > max_) max_ = *iptr[i];
	}
	return max_;
}


int main() {
    int n, i;
    int array[100];
    int *iptr[100];
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &(array[(i + 3) % n]));
        iptr[i] = &(array[(i + 3) % n]);
    }
    printf("%d\n", max(iptr, n));
    return 0;
}
