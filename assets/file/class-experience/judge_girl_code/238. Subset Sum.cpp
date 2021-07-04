# include <stdio.h>
int check(int n, int cmp, int a[], int start, static int count){
	if(cmp == 0){
		printf("OK\n");
		count++;
		return 1;
	}
	else{
		for(int i = start; i < n; i++){
			printf("i = %d\n", i);
			if(cmp > 0) return check(n, cmp - a[i], a, i, count);
		}
		return 0;
	}
	
	
	
}

int a[16];
int main(){
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	int cmp, count = 0;
	while(scanf("%d", &cmp) != EOF){
		if(check(n, cmp, a, 0, count)){
			printf("%d\n", count);
		}
	}
	
}
