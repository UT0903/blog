#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/stat.h>    
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
#define row_max 60000
#define col_max 784
#define lr 0.2
int y_train[row_max+5][10];
double x_train[row_max+2][col_max];
double x_test[10000+2][col_max];
int y_test[10000+2];
double x_t[col_max][row_max];
double W[col_max][10];
double W_grad[col_max][10];
double y_hat[row_max][10];
double ans_y_hat[10000][10];
double XW[row_max][10];
double ans[10000][10];
unsigned char xbuf[col_max];
int thread_num;
void *matrix_multi(void *cur){
    int end = (int) cur;
    for (int i = end ; i < end+(row_max/thread_num); i++){
        for (int k = 0 ; k < 10 ; k ++){
            double sum = 0;
            for (int j = 0 ; j < col_max ; j ++){
                sum += x_train[i][j]*W[j][k];
            }
            XW[i][k] = sum;
        }
    }
    pthread_exit(NULL);
    return;
}

void softmax(){
    pthread_t t[thread_num];
    void *ret[thread_num];
    for (int i = 0 ; i < thread_num ; i ++){
        int cur = i*(row_max/thread_num);
        pthread_create(&t[i], NULL, matrix_multi, (void*) cur);
    }
    for (int i = 0 ; i < thread_num ; i ++){
        pthread_join(t[i], NULL);
    }
    for (int i = 0 ; i < row_max; i ++){
        double sum = 0;
        double max = XW[i][0];
        for (int j = 1 ; j < 10 ; j ++){
            if (XW[i][j] > max) max = XW[i][j];
        }
        for (int j = 0 ; j < 10 ; j ++){
            sum += exp(XW[i][j]-max);
        }
        for (int j = 0 ; j < 10 ; j ++){
            y_hat[i][j] = exp(XW[i][j]-max)/sum;
        }
    }
    return ;
}

void update_W(){
    for (int i = 0 ; i < row_max; i ++){
        for (int j = 0 ; j < 10 ; j ++){
            y_hat[i][j] -= y_train[i][j];
        }
    }
    for (int i = 0 ; i < col_max; i++){
        for (int k = 0 ; k < 10 ; k ++){
            double sum = 0;
            for (int j = 0 ; j < row_max ; j ++){
                sum += x_t[i][j]*y_hat[j][k];
            }
            W_grad[i][k] = sum;
        } 
    }
    for (int i = 0 ; i < col_max ; i++){
        for (int j = 0 ; j < 10 ; j ++){
            W[i][j] -= lr*W_grad[i][j];
        }
    }
    return;
}

void X_trans(){
    for (int i = 0 ; i < row_max ; i++){
        for (int j = 0 ; j < col_max ; j ++){
            x_t[j][i] = x_train[i][j]; 
        }
    }
    return;
}
void init(char *argc[]){
    thread_num = atoi(argc[4]);
    FILE *fp_x = fopen(argc[1],"rb");
    FILE *fp_y = fopen(argc[2],"rb");
    FILE *fp_x_test = fopen(argc[3], "rb");
    FILE *fp_y_test = fopen("y_test", "rb");
    for (int i = 0 ; i < row_max ; i ++){    
        fread(xbuf, sizeof(char), col_max, fp_x);
        for(int j = 0 ; j < col_max; j ++){
            x_train[i][j] = (int)xbuf[j];
        }
    }
    X_trans();
    char tmpy;
    for (int i = 0 ; i < row_max; i ++){
        fscanf(fp_y,"%c",&tmpy);
        y_train[i][(int)tmpy] = 1;
    }
    for (int i = 0 ; i < 10000 ; i ++){    
        fread(xbuf, sizeof(char), col_max, fp_x_test);
        for(int j = 0 ; j < col_max; j ++){
            x_test[i][j] = ((int)xbuf[j]);
            //x_test[i][j] /= (double)255;
        }
    }
    for (int i = 0 ; i < 10000; i ++){
        fscanf(fp_y_test,"%c",&tmpy);
        y_test[i] = (int)tmpy;
        //printf("%d\n", y_test[i]);
    }
}
int main(int argv, char *argc[]){
    init(argc);
    time_t t_start, t_end;
    t_start = time(NULL);
    int n = 50;
    while(n--){
        printf("n = %d\n", n);
        softmax();
        update_W();
    }
    for(int j = 0; j < 784; j++){
        for(int k = 0; k < 10; k++){
            printf("%f%s", W[j][k], (k == 9)?"\n":" ");
        }
    }
        printf("\n\n\n\n");
    for (int i = 0 ; i < 10000; i++){
        for (int k = 0 ; k < 10 ; k ++){
            double sum = 0;
            for (int j = 0 ; j < col_max; j ++){
                sum += x_test[i][j]*W[j][k];
            }
            ans[i][k] = sum;
        }
    }
    for (int i = 0 ; i < 10000; i ++){
        double sum = 0;
        double max = ans[i][0];
        for (int j = 1 ; j < 10 ; j ++){
            if (max < ans[i][j]) max = ans[i][j];
        }
        for (int j = 0 ; j < 10 ; j ++){
            sum += exp(ans[i][j]-max);
        }
        for (int j = 0 ; j < 10 ; j ++){
            ans_y_hat[i][j] = exp(ans[i][j]-max)/sum;
        }
        
    }
    int cnt = 0;
    for (int i = 0 ; i < 10000 ; i ++){
        double max = ans_y_hat[i][0];
        int max_ind = 0;
        for (int j = 1; j < 10 ; j ++){
            if (max <= ans_y_hat[i][j]){
                max = ans_y_hat[i][j];
                max_ind = j;
            }
        }
        if (y_test[i] == max_ind) cnt ++;
    }
    t_end	= time(NULL);
    printf("time = %ld\n", t_end-t_start);
    printf("%d/10000\n", cnt);
    return 0;
}