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
#include<assert.h>
#define MAX_TIME 10000
int main(int argc, char const *argv[]){
	int pid[MAX_TIME];
	for(int i = 0; i < MAX_TIME; i++){
		if((pid[i] = fork()) == 0){
			execl(argv[1], argv[2], , NULL);
			exit(0);
		}
	}
	for(int i = 0; i < MAX_TIME; i++){
		waitpid(pid[i], NULL, 0);
	}
	return 0;
}