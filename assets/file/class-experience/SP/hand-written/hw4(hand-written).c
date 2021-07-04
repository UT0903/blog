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
pid_t double_fork(){
	pid_t pid;
	int pfd[2];
	pipe(pfd);
	if((pid = vfork()) == 0){
		if((pid = fork()) == 0){
			char tmp;
			close(pfd[1]);
			read(pfd[0], &tmp, sizeof(char));
			close(pfd[0]);
			return pid;
		}
		else{
			_exit(0);
		}
	}
	else{
		close(pfd[0]);
		wait(NULL);
		write(pfd[1], "s", sizeof(char));
		close(pfd[1]);
		return pid;
	}
}
