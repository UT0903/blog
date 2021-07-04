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
typedef struct{
	int rank, id, score;
}Person;
Person Init_person(){
	Person tmp;
	tmp.rank = 0;
	tmp.id = 0;
	tmp.score = 0;
	return tmp;
}
int cmp(const void *a, const void *b){
	Person *a_c = (Person *)a;
	Person *b_c = (Person *)b;
   	return(a_c->score - b_c->score);
}
int main(int argc, char const *argv[]){
	assert(argc == 4);
	int host_id = atoi(argv[1]), key = atoi(argv[2]), depth = atoi(argv[3]);
	int pfd[2][2][2];
	pid_t pid[2];
	FILE *fp_read1;
	FILE *fp_read2;
	FILE *fp_write1;
	FILE *fp_write2;
	//build pipe and fork (a & b)
	if(depth != 2){
		for(int i = 0; i < 2; i++){
			pipe(pfd[i][0]); pipe(pfd[i][1]);
			if((pid[i] = fork()) == 0){
				dup2(pfd[i][0][0], 0); close(pfd[i][0][0]); close(pfd[i][0][1]);
				dup2(pfd[i][1][1], 1); close(pfd[i][1][0]); close(pfd[i][1][1]);
				if(depth == 1)
					execl("./host", "host", argv[1], argv[2], "2", NULL);
				else
					execl("./host", "host", argv[1], argv[2], "1", NULL);
				exit(0);
			}
			else{
				close(pfd[i][0][0]); close(pfd[i][1][1]);
			}
		}
		fp_write1 = fdopen(pfd[0][0][1], "w");
		fp_write2 = fdopen(pfd[1][0][1], "w");
		fp_read1 = fdopen(pfd[0][1][0], "r");
		fp_read2 = fdopen(pfd[1][1][0], "r");
		//root host
		if(depth == 0){
			//open FIFO
			char name[20];
			sprintf(name, "Host%d.FIFO", host_id);
			int fd_in = open(name, O_RDWR);
			dup2(fd_in, 0); close(fd_in);
			int fd_out = open("Host.FIFO", O_RDWR);
			dup2(fd_out, 1); close(fd_out);
			while(1){
				//Init person
				Person person[8];
				for(int i = 0; i < 8; i++)
					person[i] = Init_person();
//				fprintf(stderr, "(root)message from FIFO:\n");
				//read from FIFO (c)
				for(int i = 0; i < 8; i++){
					scanf("%d", &person[i].id);
//					fprintf(stderr, "%d%s", person[i].id, (i == 7)?"\n":" ");
				}
				//write to child host (1)
				fprintf(fp_write1, "%d %d %d %d\n", person[0].id, person[1].id, person[2].id, person[3].id);
				fprintf(fp_write2, "%d %d %d %d\n", person[4].id, person[5].id, person[6].id, person[7].id);
				fflush(fp_write1);
				fflush(fp_write2);

//				fprintf(stderr, "(root)message to child:\n%s%s",buffer1, buffer2);
				if(person[0].id == -1){
//					fprintf(stderr, "ROOT FINISH!\n");
					break;
				}
				//ten times 
				for(int k = 0; k < 10; k++){
					//get message from child host(6)
					int id[2], score[2];
					fscanf(fp_read1, "%d %d", &id[0], &score[0]);
					fscanf(fp_read2, "%d %d", &id[1], &score[1]);
//					fprintf(stderr, "(root)message from child:\n%d %d\n%d %d\n", id[0], score[0], id[1], score[1]);
					//compare and accomadate(7)
					int win_id;
					if(score[0] < score[1]) win_id = id[1];	
					else win_id = id[0];
					for(int i = 0; i < 8; i++){
						if(person[i].id == win_id){
							person[i].score++;
							break;
						}
					}
					if(k < 9){
						//write winner to child(8)
						fprintf(fp_write1, "%d\n", win_id);
						fflush(fp_write1);
						fprintf(fp_write2, "%d\n", win_id);
						fflush(fp_write2);

//						fprintf(stderr, "(root)win message to child:\n%d\n", win_id);
					}
				}
				//Deal with rank(X)
				qsort(person, 8, sizeof(Person), cmp);
				int now_rank = 0, now_score = -1;
				for(int i = 7; i >= 0; i--){
					if(now_score != person[i].score){
						person[i].rank = ++now_rank;
						now_score = person[i].score;
					}
					else{
						person[i].rank = now_rank;
					}
				}
				//send message back to FIFO(X)
				printf("%d\n", key);
//				fprintf(stderr, "(root)last message to FIFO:\n%d\n", key);
				for(int i = 0; i < 8; i++){
					printf("%d %d\n", person[i].id, person[i].rank);
				}
				fflush(stdout);
			}
			//wait pid
			for(int i = 0; i < 2; i++)
				waitpid(pid[i], NULL, 0);
		}
		//child host
		else if(depth == 1){
			while(1){
				//Init person
				Person person[4];
				for(int i = 0; i < 4; i++)
					person[i] = Init_person();
				//get message from root host(1)
//				fprintf(stderr,"(child)Need message\n");
				for(int i = 0; i < 4; i++){
					scanf("%d", &person[i].id);
				}
//				fprintf(stderr, "(child)message from root:\n%d %d %d %d\n", person[0].id, person[1].id, person[2].id, person[3].id);
				//write to leaf host(2)
				fprintf(fp_write1, "%d %d\n", person[0].id, person[1].id);
				fprintf(fp_write2, "%d %d\n", person[2].id, person[3].id);
				fflush(fp_write1);
				fflush(fp_write2);

				if(person[0].id == -1){
//					fprintf(stderr, "CHILD FINISH!\n");
					break;
				}
				for(int k = 0; k < 10; k++){
					//get message from leaf(5)
					int id[2], score[2];
					fscanf(fp_read1, "%d %d", &id[0], &score[0]);
					fscanf(fp_read2, "%d %d", &id[1], &score[1]);
//					fprintf(stderr, "(child)message from leaf:\n%d %d\n%d %d\n", id[0], score[0], id[1], score[1]);
					//send message to parent(6)
					if(score[0] < score[1]){
						printf("%d %d\n", id[1], score[1]);
//						fprintf(stderr, "(child)message to root:\n%d %d\n", id[1], score[1]);
					}	
					else{
						printf("%d %d\n", id[0], score[0]);
//						fprintf(stderr, "(child)message to root:\n%d %d\n", id[0], score[0]);
					}
					fflush(stdout);
					if(k < 9){
						//get win_id from parent(8)
						int win_id;
						scanf("%d", &win_id);
//						fprintf(stderr, "(child)win message from root:\n%d\n", win_id);
						//send win_id to leaf(9)
						fprintf(fp_write1, "%d\n", win_id);
						fflush(fp_write1);
						fprintf(fp_write2, "%d\n", win_id);
						fflush(fp_write2);
					}
					
				}
			}
		}
		//wait pid
		for(int i = 0; i < 2; i++)
			waitpid(pid[i], NULL, 0);
	}
	//leaf host
	else{
		while(1){
			Person person[2];
			for(int i = 0; i < 2; i++)
				person[i] = Init_person();
			//get message from child host(2)
			for(int i = 0; i < 2; i++){
				scanf("%d", &person[i].id);
			}
            if(person[0].id == -1){
                exit(0);
            }
            char newargv[2][100];
			for(int i = 0; i < 2; i++){
				sprintf(newargv[i], "%d", person[i].id);
			}
			for(int i = 0; i < 2; i++){
				pipe(pfd[i][0]); pipe(pfd[i][1]);
				if((pid[i] = fork()) == 0){
					dup2(pfd[i][0][0], 0); close(pfd[i][0][0]); close(pfd[i][0][1]);
					dup2(pfd[i][1][1], 1); close(pfd[i][1][0]); close(pfd[i][1][1]);
//					fprintf(stderr, "exec player %s\n", newargv[i]);
					execl("./player", "player", newargv[i], NULL);
					exit(0);
				}
				else{
					close(pfd[i][0][0]); close(pfd[i][1][1]);
				}
			}
           	fp_read1 = fdopen(pfd[0][1][0], "r");
           	fp_read2 = fdopen(pfd[1][1][0], "r");
           	fp_write1 = fdopen(pfd[0][0][1], "w");
           	fp_write2 = fdopen(pfd[1][0][1], "w");
            
           	for(int k = 0; k < 10; k++){
				//get message from player(4)
				int id[2], score[2];
				fscanf(fp_read1, "%d %d", &id[0], &score[0]);
				fscanf(fp_read2, "%d %d", &id[1], &score[1]);
//				fprintf(stderr, "(leaf)message from player:\n%d %d\n%d %d\n", id[0], score[0], id[1], score[1]);
				//send message to child(5)
				if(score[0] < score[1]){
					printf("%d %d\n", id[1], score[1]);
//					fprintf(stderr, "(leaf)message to child:\n%d %d\n", id[1], score[1]);
				}	
				else{
					printf("%d %d\n", id[0], score[0]);
//					fprintf(stderr, "(leaf)message to child:\n%d %d\n", id[0], score[0]);
				}
				fflush(stdout);
	
				if(k < 9){
					//get win_id from parent(9)
					int win_id;
					scanf("%d", &win_id);
//					fprintf(stderr, "(leaf)win message from child:\n%d\n", win_id);
					//send win_id to player(10)
					fprintf(fp_write1, "%d\n", win_id);
					fflush(fp_write1);
					fprintf(fp_write2, "%d\n", win_id);
					fflush(fp_write2);
				}
			}

            fclose(fp_read1);
            fclose(fp_read2);
            fclose(fp_write1);
            fclose(fp_write2);
            for(int i = 0; i < 2; i++)
            	wait(NULL);
        }
    }
}