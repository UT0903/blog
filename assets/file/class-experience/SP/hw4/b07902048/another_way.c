#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/stat.h>    
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <signal.h>
#define PIXEL 784
#define DATA_SIZE 60000
int thread_num;
int arg[DATA_SIZE];
float lr0 = 0.02;
float lr;
float X[DATA_SIZE][PIXEL];
float W[PIXEL][10];
float y_hat[DATA_SIZE][10];
float W_grad[PIXEL][10];
int y[DATA_SIZE][10];
float X_test[10000][PIXEL];
float XW[DATA_SIZE][10];
float XW_test[10000][10];
float X_T[PIXEL][DATA_SIZE];
float W_T[10][PIXEL];
int Y_test[10000];
void Read_X_train(char *argv);
void Read_Y_train(char *argv);
void Read_X_test(char *argv);
void Read_Y_test(char *argv);
void Multi(int start, int end){
	for(int i = 0; i < 60000; ++i){
		for(int x = start; x < end; ++x){
			for(int j = 0; j < 10; ++j){
				XW[i][j] += X[i][x] * W[x][j];
			}
		}
	}
}
void *funct1(void *vptr){
	int start = (int)vptr * (PIXEL / thread_num);
	int end = fmin(((int)vptr+1) * (int)(PIXEL / thread_num), PIXEL);
	Multi(start, end);
	return NULL;
}
void funct2(){
	for(int x = 0; x < 60000; ++x){
		float max = XW[x][0], factor = 0.0;
		for(int i = 1; i < 10; ++i){
			if(XW[x][i] > max) max = XW[x][i];
		}
		for(int i = 0; i < 10; ++i){
			factor += exp(XW[x][i] - max);
		}
		for(int i = 0; i < 10; ++i){
			y_hat[x][i] = exp(XW[x][i] - max) / factor;
		}
	}
}
void funct3(){
	for(int i = 0; i < PIXEL; ++i){
		for(int j = 0; j < 10; ++j){
			W[i][j] -= lr * W_grad[i][j];
		}
	}
}
void *funct4(void *vptr){
	int start = ((int)vptr) * (DATA_SIZE / thread_num);
	int end = fmin(((int)vptr + 1) * (DATA_SIZE / thread_num), DATA_SIZE);
	
	for(int k = start; k < end; ++k){
		for(int i = 0; i < PIXEL; ++i){
			for(int j = 0; j < 10; ++j){
				W_grad[i][j] += X_T[i][k] * (y_hat[k][j] - y[k][j]);
			}
		}
	}
}

int funct1_test(){
	FILE *fp;
	fp = fopen("result.csv", "w+");
	fprintf(fp, "id,label\n");
	//fprintf(stderr, "start = %d, tid = %ld\n", start, pthread_self());
	for(int x = 0; x < 10000; ++x){
		for(int i = 0; i < 10; ++i){
			XW_test[x][i] = 0;
		}
	}
	for(int x = 0; x < 10000; ++x){
		for(int i = 0; i < PIXEL; ++i){
			float r = X_test[x][i];
			for(int j = 0; j < 10; ++j){
				XW_test[x][j] += r * W[i][j];
			}
		}
	}
	float cnt = 0;
	for(int i = 0; i < 10000; i++){
		float max = XW_test[i][0];
		int max_idx = 0;
		for(int j = 1; j < 10; j++){
			if(XW_test[i][j] > max){
				max_idx = j;
				max = XW_test[i][j];
			}
		}
		if(Y_test[i] == max_idx) cnt++;
		fprintf(fp, "%d,%d\n", i, max_idx);
	}
	fclose(fp);
	fprintf(stderr, "accur = %f\n", cnt / 10000);
}
void Cal_W_T(){
    for(int i = 0; i < PIXEL; i++){
        for(int j = 0; j < 10; j++){
            W_T[j][i] = W[i][j];
        }
    }
}
void Cal_X_T(){
	for(int i = 0; i < DATA_SIZE; ++i){
		for(int j = 0; j < 784; ++j){
			X_T[j][i] = X[i][j];
		}
	}
	for(int k = 0; k < 784; ++k){
		for(int i = 0; i < 10; ++i){
			W_grad[k][i] = 0;
		}
	}
}
void Init_XW(){
	for(int x = 0; x < 60000; ++x){
		for(int i = 0; i < 10; ++i){
			XW[x][i] = 0;
		}
	}
}
int main(int argc, char *argv[]){
	for(int i = 0; i < DATA_SIZE; i++){
		arg[i] = i;
	}
	pthread_t ntid[DATA_SIZE];
	Read_X_train(argv[1]);
	Read_Y_train(argv[2]);
	Read_X_test(argv[3]);
	thread_num = atoi(argv[4]);
	Read_Y_test(argv[5]);
	int TIMES, reduce;
	TIMES = 40;
	//training section
	for(int j = 0; j < TIMES; j++){
		lr = lr0 * pow(0.5, j / 20);
		//fprintf(stderr, "lr = %f\n", lr);
		//use thread
		Cal_W_T();
		Init_XW();
		for(int k = 0; k < thread_num; k++){
			pthread_create(&ntid[k], NULL, funct1, (void *)arg[k]);
		}
		for(int k = 0; k < thread_num; k++){
			pthread_join(ntid[k], NULL);
		}
		funct2();
		Cal_X_T();
		for(int k = 0; k < thread_num; k++){
			pthread_create(&ntid[k], NULL, funct4, (void *)arg[k]);
		}
		for(int k = 0; k < thread_num; k++){
			pthread_join(ntid[k], NULL);
		}
		funct3();
		fprintf(stderr, "Epoch = %d\n", j);
		//funct1_test();
	}
	/*for(int j = 0; j < 784; j++){
        for(int k = 0; k < 10; k++){
            printf("%f%s", W[j][k], (k == 9)?"\n":" ");
        }
    }
    printf("\n\n\n\n");*/
	funct1_test();
		//test section
		//fprintf(stderr, "Epoch = %d\n", j);
}











void Read_X_train(char *argv){
	FILE *fp;
	fp = fopen(argv, "r");
	unsigned char buf;
	//printf("x_train = ");
	for(int i = 0; i < DATA_SIZE; i++){
		for(int j = 0; j < PIXEL; j++){
			int un = fread(&buf, 1, 1, fp);
			X[i][j] = (float)buf;
			int tmp = buf;
			//printf("%3d%s", tmp, (j % 28 == 27)?"\n":" ");
		}
		//printf("\n");
	}
	fprintf(stderr, "read X_train finish\n");
	fclose(fp);
}
void Read_Y_train(char *argv){
	FILE *fp;
	fp = fopen(argv, "r");
	unsigned char buf;
	for(int i = 0; i < DATA_SIZE; i++){
		int un = fread(&buf, 1, 1, fp);
		int tmp = buf;
		y[i][tmp] = 1;
		//printf("y_train = %d\n", tmp);
	}
	fprintf(stderr, "read Y_train finish\n");
	fclose(fp);
}
void Read_X_test(char *argv){
	FILE *fp;
	fp = fopen(argv, "r");
	unsigned char buf;
	for(int i = 0; i < 10000; i++){
		for(int j = 0; j < PIXEL; j++){
			int un = fread(&buf, 1, 1, fp);
			X_test[i][j] = (float)buf;
			//printf("%lf ", X_test[i][j]);
		}
		//printf("\n");
	}
	//fprintf(stderr, "read X_test finish\n");
	fclose(fp);
}
void Read_Y_test(char *argv){
	FILE *fp;
	fp = fopen(argv, "r");
	unsigned char buf;
	for(int i = 0; i < 10000; i++){
		int un = fread(&buf, 1, 1, fp);
		Y_test[i] = buf;
		//printf("%d", Y_test[i]);
		//printf("\n");
	}
	fprintf(stderr, "read Y_test finish\n");
	fclose(fp);
}