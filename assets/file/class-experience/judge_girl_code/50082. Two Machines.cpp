# include <stdio.h>

int main()
{
	long long time_a = 0 , time_b = 0, arrived, last_a, last_b;
	while (scanf("%lld", &arrived) == 1) {
		scanf("%lld", &last_a);
		scanf("%lld", &last_b);
		time_a = (arrived > time_a ? arrived : time_a) + last_a;
		time_b = (time_a > time_b ? time_a : time_b) + last_b;
		printf("%lld\n", time_b);
	} 
} 
