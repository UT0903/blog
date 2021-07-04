#include <stdio.h>
#include <limits.h>
#define MAXN 110
typedef struct{
	int w, l;
}GET;

typedef struct{
	int num;
	int area_sum;
	GET data[MAXN];
}STACK;
STACK stack;
int w[MAXN], l[MAXN];
void push(int w, int l){
	stack.data[stack.num].w = w;
	stack.data[stack.num++].l = l;
	stack.area_sum += w * l;
}
GET pop(){
	stack.num--;
	stack.area_sum -= stack.data[stack.num].w * stack.data[stack.num].l;
	return stack.data[stack.num];
}
GET top(){
	if(stack.num - 1 < 0){
		GET tmp;
#ifdef LARGEONSMALL	
		tmp.w = 0; tmp.l = 0;
#else
		tmp.w = INT_MAX; tmp.l = INT_MAX;
#endif
		return tmp;
	}
	return stack.data[stack.num - 1];
}
#ifdef MAXAREASUM
int sum = 0, cnt, N;
#else
int sum = INT_MAX, cnt, N; 
#endif

void Find(int now){
	if(now == N){
		//printf("return\n");
		return;
	}

	Find(now + 1);
	GET tmp = top();
	//printf("stack.num = %d\n", stack.num);
#ifdef LARGEONSMALL
	if(tmp.w <= w[now] && tmp.l <= l[now]){
#else
	if(tmp.w >= w[now] && tmp.l >= l[now]){
#endif		
		//printf("push %d %d\n", w[now], l[now]);
		push(w[now], l[now]);
#ifdef MAXAREASUM
		if(stack.num == cnt && stack.area_sum > sum){
#else
		if(stack.num == cnt && stack.area_sum < sum){
#endif
			sum = stack.area_sum;
			//printf("sum = %d\n", sum);
		}		
		else if(stack.num > cnt){
			cnt = stack.num;
			sum = stack.area_sum;
			//printf("sum = %d\n", sum);
		}
		Find(now + 1);
		pop();
		return;
	}
	else{
		//printf("not good %d %d\n", w[now], l[now]);
		return;
	}
	


}


int main(){
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		scanf("%d %d", &w[i], &l[i]);
		if(w[i] > l[i]){
			int tmp = w[i];
			w[i] = l[i];
			l[i] = tmp;
		}
	}
	Find(0);
	printf("%d %d\n", cnt, sum);
}