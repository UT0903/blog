typedef unsigned long long Set;
/*void init(Set *set);
void add(Set *set, int i);
void has(Set set, int i);
Set setUnion(Set a, Set b);
Set setIntersect(Set a, Set b);
Set setDifference(Set a, Set b);*/
#include <stdio.h>
typedef unsigned long long Set;
void init(Set *set){
	*set &= 0;
	return;
}
void add(Set *set, int i){
	*set = *set | (1ll << i);
	//printf("i = %d, set = %d\n", i, *set);
	return;
}
void has(Set set, int i){
	if((set & (1ll << i)) != 0){
		printf("set has %d\n", i);
	}
	else{
		printf("set does not have %d\n", i);
	}
	return;
}
Set setUnion(Set a, Set b){
	a |= b;
	return a;
}
Set setIntersect(Set a, Set b){
	a &= b;
	return a;
}
Set setDifference(Set a, Set b){
	Set c = 0, d = 0;
	c = (a & b);
	d = (a | b);
	d = d & (~c);
	return d;
}


#include <stdio.h>
//#include "set.h"
 
int main()
{
  Set a, b, c;
 
  init(&a);
  add(&a, 3);
  add(&a, 5);
  add(&a, 2);
 //printf("a = %d\n", a);
  init(&b);
  add(&b, 3);
  add(&b, 7);
  add(&b, 9);
 //printf("b = %d\n", b);
  c = setUnion(a, b);
  has(c, 2);
  has(c, 3);
  has(c, 5);
  has(c, 7);
  has(c, 9);
 
  c = setIntersect(a, b);
  has(c, 2);
  has(c, 3);
  has(c, 5);
  has(c, 7);
  has(c, 9);
 
  c = setDifference(a, b);
  has(c, 2);
  has(c, 3);
  has(c, 5);
  has(c, 7);
  has(c, 9);
 
  return 0;
}
