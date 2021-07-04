#include <setjmp.h>
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
#define SIGUSR3 SIGWINCH
int main(){
	int fd[2];
	pid_t pid;
	char P[5], Q[5], ACK[15], arr[10000];
	int R, a[10];
	scanf("%s %s %d", P, Q, &R);
	for(int i = 0; i < R; i++){
		scanf("%d", &a[i]);
	}
	pipe(fd);

	if((pid = fork()) == 0){
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execl("./hw3", "hw3", P, Q, "3", "0", NULL);
	}
	else{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		for(int i = 0; i < R; i++){
			sleep(5);
			if(a[i] == 1) kill(pid, SIGUSR1);
			else if(a[i] == 2) kill(pid, SIGUSR2);
			else kill(pid, SIGUSR3);
			scanf("%s", ACK);
			if(strcmp(ACK, "ACK") != 0){
				for(int i = 0; i < (int)strlen(ACK); i++){
					printf("%c%s", ACK[i], (i == (int)strlen(ACK) - 1)?"\n":" ");
				}
			}
		}
		scanf("%s", arr); // read the content of arr
		waitpid(pid, NULL, 0);
		printf("%s\n", arr);
	}
	
}