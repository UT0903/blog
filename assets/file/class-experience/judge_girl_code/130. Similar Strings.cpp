# include <stdio.h>
# include <string.h>
int change(char a[], char b[]){
	int i, count = 0;
	for(i = 0; a[i] != '\0'; i++){
		if(a[i] != b[i]){
			if(a[i] != b[i+1] || b[i] != a[i+1]){
				return 0;
			}
			else{
				count++;
				i++;
			}
		}
	}
	if(count <= 1) return 1;
	else return 0;
}

int compare(char a[], char b[]){
	int i;
	for(i = 0; a[i] != '\0'; i++){
		if(a[i] != b[i]){
			return 0;
		}
	}
	//printf("yes\n");
	return 1;
}

void almost(char a[], char b[]){
	int i = 0, j = 0, count = 0;
	while(a[i] != '\0' && b[j] != '\0'){
		if(a[i] != b[j]){
			count++;
			i++;
		}
		else{
			i++;
			j++;
		}
	}
	if(count <= 1){
		printf("yes\n");
	}
	else{
		printf("no\n");
	}
}


char a[100], b[100];
int main(){
	int n, i;
	scanf("%d", &n);
	for(i = 0; i < n; i++){
		scanf("%s", a);
		scanf("%s", b);
		int x = 0, y = 0;
		if(strlen(a) == strlen(b)){
			x = compare(a, b);
			y = change(a, b);
			if(x + y >= 1) printf("yes\n");
			else printf("no\n");
		}
		else if(strlen(a) - strlen(b) == 1){
			almost(a, b);
		}
		else if(strlen(b) - strlen(a) == 1){
			almost(b, a);
		}
		else{
			printf("no\n");
		}
	}
}
