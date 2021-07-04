#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<signal.h>
#include<sys/wait.h>
int main(int argc, char const *argv[]){
	char buf[10];
	int num = atoi(argv[1]);
	int cost = num * 100;
	sprintf(buf, "%d %d\n", num, cost);
	for(int i = 0; i < 10; i++){
		write(1, buf, strlen(buf));
		char r_buf[10];
		if(i < 9) read(0, r_buf, 10);
	}
	return 0;
}