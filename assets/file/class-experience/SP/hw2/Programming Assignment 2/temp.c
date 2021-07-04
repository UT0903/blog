#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


const int NumChild = 2;


typedef struct PlayerNum {
    int playerId, number;
} PlayerNum;

int findId(int arr[], int nmemb, int val) {
    for (int i = 0; i < nmemb; ++i) {
        if (arr[i] == val) {
            return i;
        }
    }
    return -1;
}

void rank(int arr[], int nmemb) {
    int rank_result[nmemb];
    for (int i = 0; i < nmemb; ++i) {
        rank_result[i] = 1;
        for (int j = 0; j < nmemb; ++j) {
            if (arr[i] < arr[j]) {
                ++rank_result[i];
            }
        }
    }

    for (int i = 0; i < nmemb; ++i){
        arr[i] = rank_result[i];
    }
}


int main(int argc, const char **argv, const char **envp){
    assert(argc == 4);

    int hostId = atoi(argv[1]), depth = atoi(argv[3]), pipeFdPRead[2][2], pipeFdPWrite[2][2];
    fprintf(stderr, "%d\n", NumChild);
    FILE* pReadFd[NumChild]; // parent read
    FILE* pWriteFd[NumChild]; // parent write
    const char *randomKey = argv[2];

    // build up tree (fork two child comps)
    if (depth != 2) {
        for (int i = 0; i < 2; ++i) {
            pipe(pipeFdPRead[i]);
            pipe(pipeFdPWrite[i]);

            int pid = fork();
            if (pid == 0) {
                //*************
                // child part
                //*************

                // dup stdin / stdout to child before exec
                close(pipeFdPRead[i][0]);
                close(pipeFdPWrite[i][1]);
                dup2(pipeFdPRead[i][1], STDOUT_FILENO);
                dup2(pipeFdPWrite[i][0], STDIN_FILENO);
                close(pipeFdPRead[i][1]);
                close(pipeFdPWrite[i][0]);

                // execl comp
                char nextTreeDepth[100], hostIdStr[100];
                sprintf(nextTreeDepth, "%d", depth + 1);

                sprintf(hostIdStr, "%d", hostId);

                execl("./host", "host", hostIdStr, randomKey, nextTreeDepth, NULL);
                exit(0);
            }

            //*************
            // parent part
            //*************

            close(pipeFdPRead[i][1]);
            close(pipeFdPWrite[i][0]);
            pReadFd[i] = fdopen(pipeFdPRead[i][0], "r");
            pWriteFd[i] = fdopen(pipeFdPWrite[i][1], "w");
        }
    }

    // open fifo
    FILE *fp_FIFO[2];
    if (depth == 0) {
        char fifoName[100];
        sprintf(fifoName, "Host%d.FIFO", hostId);
        fp_FIFO[0] = fopen(fifoName, "r");
        fp_FIFO[1] = fopen("Host.FIFO", "w");
    }
    while (1) {
        // count number of players
        int currNumPlayer = 8;
        for (int i = 0; i < depth; ++i) {
            currNumPlayer /= 2;
        }
        int playerIdList[currNumPlayer];

        // recv player id
        int stop = 1;
        if (depth == 0) {
            // receive from FIFO
            for (int i = 0; i < currNumPlayer; ++i) {
                fscanf(fp_FIFO[0], "%d", &playerIdList[i]);
                if (playerIdList[i] != -1) {
                    stop = 0;
                }
            }
        }
        else {
            for (int i = 0; i < currNumPlayer; ++i) {
                fscanf(stdin, "%d", &(playerIdList[i]));
            }
        }



        // send player_id or -1 to child.
        if (depth != 2) {
            for (int i = 0; i < 2; ++i) {
                if(depth == 0){
                    fprintf(pWriteFd[i], "%d %d %d %d\n", playerIdList[i*4], playerIdList[i*4+1], playerIdList[i*4+2], playerIdList[i*4+3]);
                }
                else{
                    fprintf(pWriteFd[i], "%d %d\n", playerIdList[i*2], playerIdList[i*2+1]);
                }
                fflush(pWriteFd[i]);
            }
        }


        if (playerIdList[0] == -1) {
            break;
        }

        // fork player
        if (depth == 2) {
            for (int i = 0; i < 2; ++i) {
                pipe(pipeFdPRead[i]);
                pipe(pipeFdPWrite[i]);
                int pid;
                if ((pid = fork())== 0) {
                    // dup stdin / stdout to child before exec
                    close(pipeFdPRead[i][0]);
                    close(pipeFdPWrite[i][1]);
                    dup2(pipeFdPRead[i][1], STDOUT_FILENO);
                    dup2(pipeFdPWrite[i][0], STDIN_FILENO);
                    close(pipeFdPRead[i][1]);
                    close(pipeFdPWrite[i][0]);
                    char playerIdStr[100];
                    sprintf(playerIdStr, "%d", playerIdList[i]);
                    execl("./player", "player", playerIdStr, NULL);
                    exit(0);
                }
                close(pipeFdPRead[i][1]);
                close(pipeFdPWrite[i][0]);
                pReadFd[i] = fdopen(pipeFdPRead[i][0], "r");
                pWriteFd[i] = fdopen(pipeFdPWrite[i][1], "w");
            }
        }

        // 10 times
        int playerScore[8]; // for root only
        if (depth == 0) {
            for (int i = 0; i < 8; ++i) {
                playerScore[i] = 0;
            }
        }
        for (int k = 0; k < 10; k++) {
            // recv numbers from player
            PlayerNum playerNum[2];
            for (int i = 0; i < 2; ++i) {
                fscanf(pReadFd[i], "%d%d", &(playerNum[i].playerId), &(playerNum[i].number));
            }

            // send current max number to parent
            int maxI = (playerNum[0].number > playerNum[1].number)? 0 : 1;
            if(depth == 0){
                int idx = findId(playerIdList, 8, playerNum[maxI].playerId);
                playerScore[idx]++;
            }
            else{
                printf("%d %d\n", playerNum[maxI].playerId, playerNum[maxI].number);
                fflush(stdout);
            }
            // recv overall max number from parent
            int max_id;
            if (k < 9 && depth != 0) {
                fscanf(stdin, "%d", &max_id);
            }
            // send max to children
            if (k < 9) {
                for (int i = 0; i < 2; ++i) {
                    fprintf(pWriteFd[i], "%d\n", max_id);
                    fflush(pWriteFd[i]);
                }
            }
        }
        // write round result to bidding system
        if(depth == 0){
            // argsort
            rank(playerScore, 8);

            // generate output msg
            char msg[1024] = "";
            sprintf(msg, "%s\n", randomKey);
            for (int playerId = 0; playerId < 8; ++playerId) {
                sprintf(msg + strlen(msg), "%d %d\n", playerIdList[playerId], playerScore[playerId]);
            }

            //(root)write to FIFO
            fprintf(fp_FIFO[1], "%s", msg);
            fflush(fp_FIFO[1]);
        }
        // wait
        if (depth == 2) {
            for (int i = 0; i < 2; ++i) {
                wait(NULL);
                fclose(pReadFd[i]);
                fclose(pWriteFd[i]);
            }
        }
    }
    // close fifos
    if (depth == 0){
        fclose(fp_FIFO[0]);
        fclose(fp_FIFO[1]);
    }
    // wait for all children
    if (depth != 2) {
        for (int i = 0; i < 2; ++i) {
            wait(NULL);
        }
    }
    return 0;
}