# include <stdio.h>
long long max(long long w[3]){
	long long best;
	best = w[0];
	if(best < w[1]) best = w[1];
	if(best < w[2]) best = w[2]; 
	return best;
}

long long min(long long w[3]){
	long long best;
	best = w[0];
	if(best > w[1]) best = w[1];
	if(best > w[2]) best = w[2]; 
	return best;
}

long long count1(long long a[3], long long s[3], long long d[3], long long w[3]){
	long long i, sum = 0;
	for(i = 0; i < 3; i++){
		sum += (d[i] - a[i]) * (w[i] - s[i]);
	}
	return sum;
}

long long count2(long long a[3], long long s[3], long long d[3], long long w[3]){
	long long i, ww, aa, ss, dd, sum = 0;
	for(i = 0; i < 3; i++){
		if(a[i] > a[(i+1) % 3]){
			aa = a[i];
		}
		else{
			aa = a[(i+1) % 3];
		}
		
		if(d[i] < d[(i+1) % 3]){
			dd = d[i];
		}
		else{
			dd = d[(i+1) % 3];
		}
		
		if(w[i] < w[(i+1) % 3]){
			ww = w[i];
		}
		else{
			ww = w[(i+1) % 3];
		}
		
		if(s[i] > s[(i+1) % 3]){
			ss = s[i];
		}
		else{
			ss = s[(i+1) % 3];
		}
		//printf("%lld %lld %lld %lld\n", aa, ss, dd, ww);
		if((dd - aa) > 0 && (ww - ss) > 0) {
		//	printf("dd - aa = %lld ww - ss = %lld\n", dd - aa, ww - ss);
			sum += (dd - aa) * (ww - ss);
		}	
	}
	return sum;
}

long long count3(long long a[3], long long s[3], long long d[3], long long w[3]){
	long long i, ww, aa, ss, dd, sum = 0;
	ww = min(w);
	aa = max(a);
	dd = min(d);
	ss = max(s);
	
	if((dd - aa) > 0 && (ww - ss) > 0) sum += (dd - aa) * (ww - ss);	
	return sum;
}


int main(){
	long long ans;
	long long w[3] = {0}, a[3] = {0}, s[3] = {0}, d[3] = {0}, i; 
	for(i = 0; i < 3; i++){
		scanf("%lld %lld %lld %lld", &a[i], &s[i], &d[i], &w[i]);
	}
	ans = count1(a, s, d, w);
	//printf("%lld\n", ans);
	ans -= count2(a, s, d, w);
	//printf("%lld\n", ans);
	ans += count3(a, s, d, w);
	printf("%lld", ans);
	
	
}
