#pragma GCC optimize ("unroll-loops")
#pragma GCC optimization ("Ofast")
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#define MOD 1024
#define SIZE 128
#define bsize 8
void matrix_mul(unsigned short (*)[SIZE], unsigned short (*)[SIZE], unsigned short (*)[SIZE]);
int wait = 1;
int main () {
    unsigned short A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    unsigned long long start, end;

    srand(time(NULL));

    // init
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            A[i][j] = rand() % MOD;

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            B[i][j] = rand() % MOD;

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            C[i][j] = 0;
    printf("A:%hu B:%hu C:%hu\n", A[0][0], B[0][0], C[0][0]);
    asm volatile ("rdcycle %0" : "=r" (start));
    //while(wait);    
    matrix_mul(A, B, C);
    
    
    
    /*for(int jj = 0; jj < 256; jj += 16) {
        for(int kk = 0; kk < 256; kk += 16){
            for(int i = 0; i < 256; i += 2) {
                for(int j = jj; j < jj + 16; j += 2) {
                    for(int k = kk; k < kk + 16; k += 2) {
                        C[i][k] += A[i][j]*B[j][k];
                    }
                }
            }
        }
    }*/




    asm volatile ("rdcycle %0" : "=r" (end));
    //while(!wait);


    // check
    unsigned short check[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            check[i][j] = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for (int k = 0; k < SIZE; k++)
                check[i][j] = (check[i][j] + A[i][k] * B[k][j]) % MOD;

    printf("Took %llu cycles\n", end - start);
    printf("A:%hu B:%hu C:%hu check:%hu\n", A[0][0], B[0][0], C[0][0], check[0][0]);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            assert(check[i][j] == C[i][j]);
    }
void matrix_mul(unsigned short A[][SIZE], unsigned short B[][SIZE], unsigned short C[][SIZE]){
    for(int jj = 0; jj < SIZE; jj += bsize) {
        for(int kk = 0; kk < SIZE; kk += bsize){
            for(int i = 0; i < SIZE; i++) {
                for(int j = jj; j < jj + bsize; j++) {
                    sum = C[i][j];
                    for(int k = kk; k < kk + bsize; k++) {
                        sum += A[i][j]*B[j][k];
                    }
                    C[i][j] = sum;
                }
            }
        }
    }
    
    int *i;
    for(i = &C[0][0]; i < &C[SIZE][SIZE]; i++){
        *i &= 1023;
    }
}