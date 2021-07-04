#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/stat.h>    
#include <fcntl.h>
#include <math.h>
#include <immintrin.h>
typedef struct{
    int row, col;
    float values[8][8];
}Matrix;
void SIMD_AVX_matmul8(Matrix l, Matrix r, Matrix dst, int c_row, int c_col){
    __m256 I[8], R[8], S[8], Sum[8];
    __m256i mask;

    for (int i = 0; i < 8; i++)
        Sum[i] = _mm256_setzero_ps();

    for (int k = 0; k < l.col; k += 8){
        for (int i = 0; i < 8 && k + i < r.row; i++){
            if (c_col + 8 <= r.col)
                R[i] = _mm256_loadu_ps((float*) (&r.values[k + i][c_col]));
            else{
                int iMask[8];
                for (int j = 0; j < 8; j++){
                    iMask[j] = c_col + j < r.col? 1 << 31 : 0;
                }
                mask = _mm256_setr_epi32(iMask[0], iMask[1], iMask[2], iMask[3],
                                      iMask[4], iMask[5], iMask[6], iMask[7]);
                R[i] = _mm256_maskload_ps((float *) (&r.values[k + i][c_col]), mask);
            }
        }


        for (int i = 0; i < 8 && c_row + i < l.row; i++){
            for (int j = 0; j < 8 && k + j < l.col; j++){
                I[j] = _mm256_set1_ps(l.values[c_row + i][k + j]);
                S[j] = _mm256_mul_ps(R[j], I[j]);
            }
            for (int j = 0; j < 8 && k + j < l.col; j++)
                Sum[i] = _mm256_add_ps(Sum[i], S[j]);
        }
    }

    for (int i = 0; i < 8 && c_row + i < l.row; i++) {
        if (c_col + 8 <= r.col)
            _mm256_storeu_ps((float *) (&dst.values[c_row + i][c_col]), Sum[i]);
        else
            _mm256_maskstore_ps(&dst.values[c_row + i][c_col], mask, Sum[i]);
    }
}

void SIMD_AVX_matmul(Matrix l, Matrix r, Matrix dst){
    for (int i = 0; i < l.row; i += 8)
        for (int j = 0; j < r.col; j += 8)
            SIMD_AVX_matmul8(l, r, dst, i, j);
}

int main(){
    Matrix a, b, c;
    a.row = a.col = 8;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            a.values[i][j] = 1.0;
        }
    }
    b.row = b.col = 8;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            b.values[i][j] = 1.0;
        }
    }
    c.row = c.col = 8;
    SIMD_AVX_matmul(a,b, c);
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            printf("%f%s", c.values[i][j], (j == 7)?"\n":" ");
        }
    }
}