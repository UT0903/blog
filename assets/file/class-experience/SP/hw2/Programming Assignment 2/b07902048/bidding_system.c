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
typedef struct{
	int score, rank, id;
}Person;
int cmp2(const void *a, const void *b){
	Person *a_c = (Person *)a;
	Person *b_c = (Person *)b;
   	return(a_c->id - b_c->id);
}
int cmp(const void *a, const void *b){
	Person *a_c = (Person *)a;
	Person *b_c = (Person *)b;
   	return(b_c->score - a_c->score);
}
int Is_finish(int finish[11], int host_num){
	for(int i = 1; i <= host_num; i++){
		if(finish[i] == 0) return 0;
	}
	return 1;
}
void Assign(int fd, char *buf){
	write(fd, buf, strlen(buf));
}
int main(int argc, char const *argv[]){
	int host_num = atoi(argv[1]), play_num = atoi(argv[2]);
    int fd[11];
    //make fifo & unlink it
	mkfifo("Host.FIFO", 0644);
	fd[0] = open("Host.FIFO", O_RDWR);
	for(int i = 1; i <= host_num; i++){
		//fprintf(stderr, "i = %d\n", i);
		char name[20];
		sprintf(name, "Host%d.FIFO", i);
		mkfifo(name, 0644);
		fd[i] = open(name, O_RDWR);
	}
	//set message
	char message[3010][30];
	int message_max = 0;
	for(int a = 1; a <= play_num; a++){
		for(int b = a+1; b <= play_num; b++){
			for(int c = b+1; c <= play_num; c++){
				for(int d = c+1; d <= play_num; d++){
					for(int e = d+1; e <= play_num; e++){
						for(int f = e+1; f <= play_num; f++){
							for(int g = f+1; g <= play_num; g++){
								for(int h = g+1; h <= play_num; h++){
									sprintf(message[message_max++], "%d %d %d %d %d %d %d %d\n", a, b, c, d, e, f, g, h);
								}
							}
						}
					}
				}
			}
		}
	}
	//fork
	pid_t pid[15];
	for(int i = 1; i <= host_num; i++){
		if((pid[i] = fork()) == 0){
			char var[4];
			sprintf(var, "%d", i);
			execl("./host", "host", var, var, "0", NULL);
			exit(0);
		}
	}
	//rank Init
	Person person[14];
	for(int i = 0; i < play_num; i++){
		person[i].score = 0;
		person[i].rank = 0;
		person[i].id = i + 1;
	}
	//send message to root host
	char end_message[30] = "-1 -1 -1 -1 -1 -1 -1 -1\n";
	int now = 0;
	int finish[11] = {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char back[1024];
	char delim[2] = " \n";
	for(int i = 1; i <= host_num; i++){
		if(now < message_max){
			Assign(fd[i], message[now]);
			now++;
		}
		else{
			Assign(fd[i], end_message);
			//sleep(1);
			close(fd[i]);
			finish[i] = 1;
		}
	}
	int key;
	dup2(fd[0], 0);
	while(!Is_finish(finish, host_num)){
		if(scanf("%d", &key) != EOF){
			int id[8], rank[8];
			//int key = atoi((char *)strtok(back, delim));
			//fprintf(stderr, "now = %d, message_max = %d\n", now, message_max);
			for(int i = 0; i < 8; i++){
				scanf("%d %d", &id[i], &rank[i]);
				//id[i] = atoi((char *)strtok(NULL, delim));
				//rank[i] = atoi((char *)strtok(NULL, delim));
				//fprintf(stderr, "%d %d\n", id[i], rank[i]);
			}
			//printf("%d %d\n", id[0], rank[0]);
			if(now >= message_max){
				if(finish[key] == 0){
					Assign(fd[key], end_message);
					//sleep(2);
					close(fd[key]);
					finish[key] = 1;
				}
			}
			else{
				Assign(fd[key], message[now]);
				now++;
			}
			//accomulation
			for(int i = 0; i < 8; i++){
				person[id[i] - 1].score += (8 - rank[i]);
			}
			//printf("finish\n");
		}
	}
	//wait pid
	//printf("here\n");
	unlink("Host.FIFO");
	for(int i = 1; i <= host_num; i++){
		waitpid(pid[i], NULL, 0);
		char name[20];
		sprintf(name, "Host%d.FIFO", i);
		unlink(name);
	}
	//Output winner
	int now_rank = 0, now_score = -1;
	qsort(person, play_num, sizeof(Person), cmp);
	for(int i = 0; i < play_num; i++){
		if(now_score != person[i].score){
			person[i].rank = ++now_rank;
			now_score = person[i].score;
		}
		else
			person[i].rank = now_rank;
	}
	qsort(person, play_num, sizeof(Person), cmp2);
	for(int i = 0; i < play_num; i++){
		printf("%d %d\n", person[i].id, person[i].rank);
	}
	return 0;
}