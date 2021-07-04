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
#include <immintrin.h>
#define PIXEL 784
#define DATA_SIZE 60000
int thread_num;
int arg[100];
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
float y_hat_y_T[10][DATA_SIZE];
float W_T[10][PIXEL];
int Y_test[10000];
void Read_X_train(char *argv);
void Read_Y_train(char *argv);
void Read_X_test(char *argv);
void Read_Y_test(char *argv);
void Multi(int start, int end){
	for(int x = start; x < end; ++x){
		for(int i = 0; i < 10; ++i){
			XW[x][i] = 0;
		}
	}

	/*for(int x = start; x < end; ++x){
		for(int i = 0; i < PIXEL; ++i){
			float r = X[x][i];
			for(int j = 0; j < 10; ++j){
				XW[x][j] += r * W[i][j];
			}
		}
	}*/
	__m256 ymm[16];
    float scratchpad[8];
    for(int l = start; l < end; l++){
        for(int k = 0; k < 10; k++){
            for(int j = 0; j < 12; j++){
                for(int i = 0; i < 8; i++){
                    ymm[i] = __builtin_ia32_loadups256(&X[l][(i << 3)+(j << 6)]);
                    ymm[i+8] = __builtin_ia32_loadups256(&W_T[k][(i << 3)+(j << 6)]);
                }
                for(int i = 0; i < 8; i++){
                    ymm[i] = __builtin_ia32_mulps256(ymm[i], ymm[i+8]);
                }
                for(int i = 1; i < 8; i++){
                    ymm[0] = __builtin_ia32_addps256(ymm[0], ymm[i]);
                }
                __builtin_ia32_storeups256(scratchpad, ymm[0]);
                for(int i = 0; i < 8; i++) XW[l][k] += scratchpad[i];
            }
        	for(int i = 768; i < 784; i++){
        		XW[l][k] += X[l][i] * W_T[k][i];
        	}
        }
    }
}
void *funct1(void *vptr){
	int start = (int)vptr * (DATA_SIZE / thread_num);
	int end = ((int)vptr+1) * (DATA_SIZE / thread_num);
	//fprintf(stderr, "start = %d, tid = %ld\n", start, pthread_self());
	Multi(start, end);
	//softmax
	for(int x = start; x < end; ++x){
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
	for(int i = start; i < end; i++){
        for(int j = 0; j < 10; j++){
            y_hat_y_T[j][i] = y_hat[i][j] - y[i][j];
        }
    }
	return NULL;
}
void funct3(){
	for(int i = 0; i < PIXEL; ++i){
		for(int j = 0; j < 10; ++j){
			W[i][j] -= lr * W_grad[i][j];
		}
	}
}
void *funct4(void *vptr){
	int start = (int)vptr * 28;
	int end = start + 28;
	for(int i = 0; i < DATA_SIZE; ++i){
		for(int j = start; j < end; ++j){
			X_T[j][i] = X[i][j];
		}
	}
	for(int k = start; k < end; ++k){
		for(int i = 0; i < 10; ++i){
			W_grad[k][i] = 0;
		}
	}
	
	__m256 ymm[16];
    float scratchpad[8];
    for(int l = start; l < end; l++){
        for(int k = 0; k < 10; k++){
            for(int j = 0; j < 937; j++){
                for(int i = 0; i < 8; i++){
                    ymm[i] = __builtin_ia32_loadups256(&X_T[l][(i << 3) + (j << 6)]);
                    ymm[i+8] = __builtin_ia32_loadups256(&y_hat_y_T[k][(i << 3) +(j << 6)]);
                }
                for(int i = 0; i < 8; i++){
                    ymm[i] = __builtin_ia32_mulps256(ymm[i], ymm[i+8]);
                }
                for(int i = 1; i < 8; i++){
                    ymm[0] = __builtin_ia32_addps256(ymm[0], ymm[i]);
                }
                __builtin_ia32_storeups256(scratchpad, ymm[0]);
                for(int i = 0; i < 8; i++) W_grad[l][k] += scratchpad[i];
            }
        	for(int i = 59968; i < 60000; i++){
                W_grad[l][k] += X_T[l][i] * y_hat_y_T[k][i];
            }
        }
    }

    /*
	for(int k = start; k < end; ++k){
		for(int i = 0; i < DATA_SIZE; ++i){
			float r = X_T[k][i];
			for(int j = 0; j < 10; ++j){
				W_grad[k][j] += r * (y_hat[i][j] - y[i][j]);
			}
		}
	}*/
}
void funct4_(){
	for(int i = 0; i < DATA_SIZE; ++i){
		for(int j = 0; j < PIXEL; ++j){
			X_T[j][i] = X[i][j];
		}
	}
	for(int k = 0; k < PIXEL; ++k){
		for(int i = 0; i < 10; ++i){
			W_grad[k][i] = 0;
		}
	}

    __m256 ymm[16];
    float scratchpad[8];
    for(int l = 0; l < 784; l++){
        for(int k = 0; k < 10; k++){
            for(int j = 0; j < 937; j++){
                for(int i = 0; i < 8; i++){
                    ymm[i] = __builtin_ia32_loadups256(&X_T[l][(i << 3) +(j << 6)]);
                    ymm[i+8] = __builtin_ia32_loadups256(&y_hat_y_T[k][(i << 3)+(j << 6)]);
                }
                for(int i = 0; i < 8; i++){
                    ymm[i] = __builtin_ia32_mulps256(ymm[i], ymm[i+8]);
                }
                for(int i = 1; i < 8; i++){
                    ymm[0] = __builtin_ia32_addps256(ymm[0], ymm[i]);
                }
                __builtin_ia32_storeups256(scratchpad, ymm[0]);
                for(int i = 0; i < 8; i++) W_grad[l][k] += scratchpad[i];
            }
        	for(int i = 59968; i < 60000; i++){
                W_grad[l][k] += X_T[l][i] * y_hat_y_T[k][i];
            }
        }
    }

    
	/*for(int k = 0; k < PIXEL; ++k){
		for(int i = 0; i < DATA_SIZE; ++i){
			float r = X_T[k][i];
			for(int j = 0; j < 10; ++j){
				W_grad[k][j] += r * (y_hat[i][j] - y[i][j]);
			}
		}
	}*/
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
		//if(Y_test[i] == max_idx) cnt++;
		fprintf(fp, "%d,%d\n", i, max_idx);
	}
	fclose(fp);
	//fprintf(stderr, "accur = %f\n", cnt / 10000);
}
void Cal_W_T(){
    for(int i = 0; i < PIXEL; i++){
        for(int j = 0; j < 10; j++){
            W_T[j][i] = W[i][j];
        }
    }
}

int main(int argc, char *argv[]){
	for(int i = 0; i < 100; i++){
		arg[i] = i;
	}
	pthread_t ntid[100];
	Read_X_train(argv[1]);
	Read_Y_train(argv[2]);
	Read_X_test(argv[3]);
	thread_num = atoi(argv[4]);
	//Read_Y_test(argv[5]);
	int TIMES, reduce;
	//training section
	for(int j = 0; j < TIMES; j++){
		lr = lr0 * pow(0.5, j / 20);
		//fprintf(stderr, "lr = %f\n", lr);
		//use thread
		Cal_W_T();
		for(int k = 0; k < thread_num; k++){
			pthread_create(&ntid[k], NULL, funct1, (void *)arg[k]);
		}
		for(int k = 0; k < thread_num; k++){
			pthread_join(ntid[k], NULL);
		}
		//funct2();
		if(thread_num > 28){
			for(int k = 0; k < 28; k++){
				pthread_create(&ntid[k], NULL, funct4, (void *)arg[k]);
			}
			for(int k = 0; k < 28; k++){
				pthread_join(ntid[k], NULL);
			}
		}
		else{
			funct4_();
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