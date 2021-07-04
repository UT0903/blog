# include <stdio.h>
# include <ctype.h>

int arr[150] = {0};
int main(){
	char n;
	while(scanf("%c", &n) != EOF){
		if(isalpha(n)){
			n = tolower(n);
		}
		n = (int)n;
		arr[n]++;
	}
	int i, a, z;
	a = (int)'a';
	z = (int)'z';
	for(i = a; i <= z; i++){
		printf("%d\n", arr[i]);
	}
}
