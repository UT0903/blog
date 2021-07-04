# include <stdio.h>

int main(){
	int a[101] = {0}, guess[101] = {0}, n, p, pass = 0, i, k = 0;
	scanf("%d %d", &n, &p);
	printf("You set N = %d , P = %d \n" , n , p );
	while(!pass){
		for(i = 0; i < p; i++){
			scanf("%d", &a[i]);
			if(a[i] > n || a[i] < 1){
					printf("The answer is illegal, please reset the answer.");
					break;
			}
			else k++;
			if (k == p) pass = 1;
		}
	}
	printf("ans:");
	int j, fin = 0, a_full[101], guess_full[101];
	for(i = 0; i < p; i++) printf(" %d", a[i]);
	printf("\n");
	
	while(!fin){
		for(i = 0; i < 101; i++){
			a_full[i] = 0;
			guess_full[i] = 0;
		}
		int h = 0, x = 0;
		for(i = 0; i < p; i++) scanf("%d", &guess[i]);
		printf("guess:");
		for(i = 0; i < p; i++) printf(" %d", guess[i]);
		printf("\n");
		for(i = 0; i < p; i++){
			if(a[i] == guess[i]){
				h++;
				a_full[i] = 1;
				guess_full[i] = 1;
			}
		}
		for(i = 0; i < p; i++){
			if(a_full[i] != 1){
				for(j = 0; j < p; j++){
					if(a[i] == guess[j] && guess_full[j] != 1){
						x++;
						a_full[i] = 1;
						guess_full[j] = 1;
						break;
					}
				}	
			}
		}
		
		printf("%dH %dX\n", h, x);
		if(h == p) fin = 1;
	}
}
