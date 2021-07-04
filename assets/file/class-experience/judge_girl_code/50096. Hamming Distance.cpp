# include <stdio.h>


int valid[30];
unsigned long long int a;
int tmp[100];
int check;
int main(){
	int n, p, s;
	scanf("%d %d %d", &n, &p, &s);
	int m = 0;
	for(int i = 0; i < p; i++){
		scanf("%llu", &a);
		for(int j = 0; j < 64; j++){
			tmp[j] = a % 2;
			a = a >> 1;
			//printf("%d%s", tmp[j], (j % 8 == 7)? "\n" : " ");
		}
		for(int w = 7;w >= 0; w--){
			int f = 128;
			for(int j = 7; j >= 0; j--){
				if(m == n) break;
				valid[m] += (tmp[(w * 8 + j)] * f);
				f /= 2;
			}
			//printf("valid[%d] = %d\n", m, valid[m]);
			m++;
		}
		
		
	}

	for(int x = 0; x < s; x++){
		scanf("%d", &check);
		//printf("check = %d\n", check);
		
		for(int y = 0; y < n; y++){
			int count = 0;
			for(int w = 0; w < 8; w++){
				if(((valid[y] >> w) & 1) != ((check >> w) & 1)) count++;
			}
			if(count <= 1){
				printf("%d\n", valid[y]);
				break;
			}
		}
	}
	
}

