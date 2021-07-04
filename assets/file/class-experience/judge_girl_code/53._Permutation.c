#include <stdio.h>
int n, a[10000000], check[10000000];
void print(int count){
	printf("count = %d\n", count);
	if(count == n){
		printf("\n");
		return;
	}
	for(int i = 0; i < n; i++){
		if(check[i] == 0){
			check[i] == 1;
			printf("%d ", a[i]);
			print(count + 1);
		}
	}
	//printf("\n");
	return;

}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	for(int i = 0; i < n; i++){
		for(int j = i; j < n; j++){
			if(a[i] > a[j]){
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
	/*for(int i = 0; i < n; i++){
		printf("%d ", a[i]);
	}*/
	print(0);
	return 0;
}