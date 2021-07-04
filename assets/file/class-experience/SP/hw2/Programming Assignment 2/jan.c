#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

void process_filename(char *root_FIFO, char *FIFO, int host_id){
    const char prefix[20] = "Host", suffix[20] = ".FIFO";
    sprintf(root_FIFO, "%s%s", prefix, suffix);
    sprintf(FIFO, "%s%d%s", prefix, host_id, suffix);
    return;
}

void close_all(int fd[2][2]){
    close(fd[0][0]);
    close(fd[0][1]);
    close(fd[1][0]);
    close(fd[1][1]);
    return;
}

void finish_ranking(int rank[], int players[], int scoreboard[]){
    for(int i = 1; i <= 8; i++)
        rank[i] = 1;
    for(int i = 1; i <= 8; i++)
        for(int j = 1; j <= 8; j++)
            if(scoreboard[players[j]] > scoreboard[players[i]])
                rank[i]++;
    return;
}

void handle_competition(FILE *fp1, FILE *fp2){
    //fprintf(stderr, "fuck buf1 = %s buf2 = %s\n", buf1, buf2);
    int p1, m1, p2, m2;
    fscanf(fp1, "%d%d", &p1, &m1);
    fscanf(fp2, "%d%d", &p2, &m2);
    //fprintf(stderr, "p1 = %d m1 = %d p2 = %d m2 = %d\n", p1, m1, p2, m2);
    char buf[40];
    if(m1 > m2){
        //fprintf(stderr, "p1 = %d m1 = %d\n", p1, m1);
        sprintf(buf, "%d %d\n", p1, m1);
        printf("%s", buf);
        fflush(stdout);
        fsync(STDOUT_FILENO);
    }
    else{
        //fprintf(stderr, "fuck p2 = %d m2 = %d\n", p2, m2);
        sprintf(buf, "%d %d\n", p2, m2);
        printf("%s", buf);
        fflush(stdout);
        fsync(STDOUT_FILENO);
    }
    return;
}

int main(int argc, char **argv){
    int host_id = atoi(argv[1]), random_key = atoi(argv[2]), depth = atoi(argv[3]);
    if(depth == 0){
        int fd[2][2], fd2[2][2]; 
        pipe(fd[0]);
        pipe(fd[1]);
        pipe(fd2[0]);
        pipe(fd2[1]); 
        if(fork() == 0){
            dup2(fd[0][0], 0);
            dup2(fd[1][1], 1);
            close_all(fd);
            close_all(fd2);
            execlp("./host", "./host", argv[1], argv[2], "1", NULL);
        }
        else if(fork() == 0){
            dup2(fd2[0][0], 0);
            dup2(fd2[1][1], 1);
            close_all(fd);
            close_all(fd2);
            execlp("./host", "./host", argv[1], argv[2], "1", NULL);
        }
        else{
            close(fd[0][0]);
            close(fd[1][1]);
            close(fd2[0][0]);
            close(fd2[1][1]);
            char root_FIFO[20], FIFO[20];
            process_filename(root_FIFO, FIFO, host_id);
            FILE *readfp = fopen(FIFO, "r");
            FILE *writefp = fopen(root_FIFO, "w");
            FILE *fp1 = fdopen(fd[1][0], "r");
            FILE *fp2 = fdopen(fd2[1][0], "r");
            FILE *writefp1 = fdopen(fd[0][1], "w");
            FILE *writefp2 = fdopen(fd2[0][1], "w");
            int writefd = fileno(writefp);
            int writefd1 = fileno(writefp1);
            int writefd2 = fileno(writefp2);
            while(1){
                int players[10];
                int rank[20], scoreboard[20] = {};
                fscanf(readfp, "%d%d%d%d%d%d%d%d", &players[1], &players[2], &players[3], &players[4], &players[5], &players[6], &players[7], &players[8]);
                //fprintf(stderr, "root players: %d %d %d %d %d %d %d %d\n", players[1], players[2], players[3], players[4], players[5], players[6], players[7], players[8]);
                fprintf(writefp1, "%d %d %d %d\n", players[1], players[2], players[3], players[4]);
                fflush(writefp1);
                fsync(writefd1);
                fprintf(writefp2, "%d %d %d %d\n", players[5], players[6], players[7], players[8]);
                fflush(writefp2);
                fsync(writefd2);
                if(players[1] == -1)
                    break;
                for(int round = 1; round <= 10; round++){
                    int p1, m1, p2, m2, winner;
                    fscanf(fp1, "%d%d", &p1, &m1);
                    fscanf(fp2, "%d%d", &p2, &m2);
                    //fprintf(stderr, "root: p1 = %d m1 = %d p2 = %d m2 = %d\n", p1, m1, p2, m2);
                    winner = (m1 > m2)? p1 : p2;
                    scoreboard[winner]++;
                    if(round < 10){
                        fprintf(writefp1, "%d\n", winner);
                        fflush(writefp1);
                        fsync(writefd1);
                        fprintf(writefp2, "%d\n", winner);
                        fflush(writefp2);
                        fsync(writefd2);
                    }
                }
                finish_ranking(rank, players, scoreboard);
                fprintf(writefp, "%d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n", random_key, players[1], rank[1], players[2], rank[2], players[3], rank[3], players[4], rank[4], players[5], rank[5], players[6], rank[6], players[7], rank[7], players[8], rank[8]);
                fflush(writefp);
                fsync(writefd);
            }
            fclose(readfp);
            fclose(writefp);
            fclose(fp1);
            fclose(fp2);
            fclose(writefp1);
            fclose(writefp2);
            close_all(fd);
            close_all(fd2);
            wait(NULL);
            wait(NULL);
            exit(0);
        }
    }
    else if(depth == 1){
        int fd[2][2], fd2[2][2];
        pipe(fd[0]);
        pipe(fd[1]);
        pipe(fd2[0]);
        pipe(fd2[1]);
        if(fork() == 0){
            dup2(fd[0][0], 0);
            dup2(fd[1][1], 1);
            close_all(fd);
            close_all(fd2);
            execlp("./host", "./host", argv[1], argv[2], "2", NULL);
        }
        else if(fork() == 0){
            dup2(fd2[0][0], 0);
            dup2(fd2[1][1], 1);
            close_all(fd);
            close_all(fd2);
            execlp("./host", "./host", argv[1], argv[2], "2", NULL);
        }
        else{
            close(fd[0][0]);
            close(fd[1][1]);
            close(fd2[0][0]);
            close(fd2[1][1]);
            FILE *fp1 = fdopen(fd[1][0], "r");
            FILE *fp2 = fdopen(fd2[1][0], "r");
            FILE *writefp1 = fdopen(fd[0][1], "w");
            FILE *writefp2 = fdopen(fd2[0][1], "w");
            int writefd1 = fileno(writefp1);
            int writefd2 = fileno(writefp2);
            while(1){
                int players[10];
                scanf("%d%d%d%d", &players[1], &players[2], &players[3], &players[4]);
                //fprintf(stderr, "child players: %d %d %d %d\n", players[1], players[2], players[3], players[4]);
                fprintf(writefp1, "%d %d\n", players[1], players[2]);
                fflush(writefp1);
                fsync(writefd1);
                fprintf(writefp2, "%d %d\n", players[3], players[4]);
                fflush(writefp2);
                fsync(writefd2);
                if(players[1] == -1)
                    break;
                for(int round = 1; round <= 10; round++){
                    //handle_competition(fp1, fp2);
                    int p1, m1, p2, m2;
                    fscanf(fp1, "%d%d", &p1, &m1);
                    fscanf(fp2, "%d%d", &p2, &m2);
                    //fprintf(stderr, "Child: p1 = %d m1 = %d p2 = %d m2 = %d\n", p1, m1, p2, m2);
                    if(m1 > m2){
                        printf("%d %d\n", p1, m1);
                        fflush(stdout);
                        fsync(STDOUT_FILENO);
                    }
                    else{
                        printf("%d %d\n", p2, m2);
                        fflush(stdout);
                        fsync(STDOUT_FILENO);
                    }
                    if(round < 10){
                        int winner;
                        scanf("%d", &winner);
                        fprintf(writefp1, "%d\n", winner);
                        fflush(writefp1);
                        fsync(writefd1);
                        fprintf(writefp2, "%d\n", winner);
                        fflush(writefp2);
                        fsync(writefd2);
                    }
                }
            }
            fclose(fp1);
            fclose(fp2);
            fclose(writefp1);
            fclose(writefp2);
            close_all(fd);
            close_all(fd2);
            wait(NULL);
            wait(NULL);
            exit(0);
        }
    }
    else if(depth == 2){
        while(1){
            int fd[2][2], fd2[2][2];
            pipe(fd[0]);
            pipe(fd[1]);
            pipe(fd2[0]);
            pipe(fd2[1]);
            FILE *fp1 = fdopen(fd[1][0], "r");
            FILE *fp2 = fdopen(fd2[1][0], "r");
            FILE *writefp1 = fdopen(fd[0][1], "w");
            FILE *writefp2 = fdopen(fd2[0][1], "w");
            int writefd1 = fileno(writefp1);
            int writefd2 = fileno(writefp2);
            int players[10];
            scanf("%d%d", &players[1], &players[2]);
            //fprintf(stderr, "Leaf players: %d %d\n", players[1], players[2]);
            if(players[1] == -1){
                fclose(fp1);
                fclose(fp2);
                fclose(writefp1);
                fclose(writefp2);
                close_all(fd);
                close_all(fd2);
                exit(0);
            }
            if(fork() == 0){
                dup2(fd[0][0], 0);
                dup2(fd[1][1], 1);
                close_all(fd);
                close_all(fd2);
                fclose(fp1);
                fclose(fp2);
                fclose(writefp1);
                fclose(writefp2);
                char arg[10];
                sprintf(arg, "%d", players[1]);
                execlp("./player", "./player", arg, NULL);
            }
            else if(fork() == 0){
                dup2(fd2[0][0], 0);
                dup2(fd2[1][1], 1);
                close_all(fd);
                close_all(fd2);
                fclose(fp1);
                fclose(fp2);
                fclose(writefp1);
                fclose(writefp2);
                char arg[10];
                sprintf(arg, "%d", players[2]);
                execlp("./player", "./player", arg, NULL);
            }
            else{
                close(fd[0][0]);
                close(fd[1][1]);
                close(fd2[0][0]);
                close(fd2[1][1]);
                for(int round = 1; round <= 10; round++){
                    //handle_competition(fp1, fp2);
                    int p1, m1, p2, m2;
                    fscanf(fp1, "%d%d", &p1, &m1);
                    fscanf(fp2, "%d%d", &p2, &m2);
                    //fprintf(stderr, "Leaf: p1 = %d m1 = %d p2 = %d m2 = %d\n", p1, m1, p2, m2);
                    if(m1 > m2){
                        printf("%d %d\n", p1, m1);
                        fflush(stdout);
                        fsync(STDOUT_FILENO);
                    }
                    else{
                        printf("%d %d\n", p2, m2);
                        fflush(stdout);
                        fsync(STDOUT_FILENO);
                    }
                    if(round < 10){
                        int winner;
                        scanf("%d", &winner);
                        fprintf(writefp1, "%d\n", winner);
                        fflush(writefp1);
                        fsync(writefd1);
                        fprintf(writefp2, "%d\n", winner);
                        fflush(writefp2);
                        fsync(writefd2);
                    }
                }
                fclose(fp1);
                fclose(fp2);
                fclose(writefp1);
                fclose(writefp2);
                close_all(fd);
                close_all(fd2);
                wait(NULL);
                wait(NULL);
            }
        }
    }
}
