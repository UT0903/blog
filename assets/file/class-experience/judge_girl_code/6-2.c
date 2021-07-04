#include <stdio.h>
int main()
{
	int n, i, a[100], up[100], down[100];
	scanf("%d", &n);
	for (i = 0; i < n; i++){
	scanf("%d", &a[i]);
	}
	for (i = 0; i < n; i++){
	if (i%2==1){
		up[(i-1)/2] = a[i];
	}
	else {
		down[(i-2)/2] = a[i];
	}
	}
	for (i = 0; i < (n/2); i++){
	printf("%d ", (up[i]));
	}
	printf("\n");
	for (i = 0; i < (n/2); i++){
	printf("%d ", (down[i]));
	}
}
