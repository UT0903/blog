# include <stdio.h>

int main(){
	long long a, b, c, i, d, e, f, k = 0;
	long long ans[3] = {100001,100001,100001};
	scanf("%lld %lld %lld", &a, &b, &c);
	for (i = -100000; i <= 100000; i++ ){
		if (i*i*i + a*i*i + b*i + c == 0){
			ans[k] = i;
			k++;
		}
	}
	//printf("%d %d %d\n", ans[0], ans[1], ans[2]);
	
	if ( ans[1] == 100001){
		ans[1] = ans[0];
		ans[2] = ans[1];
	}
	else if ( ans[2] == 100001){
		if ( ans[0] * ans[1] * ans[1] == -c && ans[0] + ans[1] + ans[1] == -a ) ans[2] = ans[1];
		else if (ans[0] * ans[0] * ans[1] == -c && ans[0] + ans[0] + ans[1] == -a){
			ans[2] = ans[1];
			ans[1] = ans[0];
		}
	}
	
	f = -ans[0];
	e = -ans[1];
	d = -ans[2];
	printf("%d %d %d", d, e, f);
}
