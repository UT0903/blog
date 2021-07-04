#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
int main(){
	FILE *fp;
	fp = fopen("time.csv", "w+");
	fprintf(fp, "thread_num,time\n");
	struct timeval start, end;
	pid_t pid;
	for(int i = 2; i <= 3; i++){
		char buf[10];
		sprintf(buf, "%d", i);
		gettimeofday(&start, NULL);
		if((pid = fork()) == 0){
			execl("hw4", "hw4", "X_train", "y_train", "X_test", buf, NULL);
		}
		waitpid(pid, NULL, 0);
		gettimeofday(&end, NULL);
		int timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;
		fprintf(fp, "%d,%d\n", i, timeuse); 
	}
	fclose(fp);
}