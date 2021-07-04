// See LICENSE for license details.
#include "dataset.h"
#include "util.h"
#include <stddef.h>
#define blockSize 4
#define block 16
#pragma GCC optimize ("unroll-loops")  
#pragma GCC optimize ("O3")
void matmul(const size_t coreid, const size_t ncores, const size_t lda,  const data_t A[], const data_t B[], data_t C[])
{
  size_t i, j, k, i0, j0, k0;
  //size_t block = lda / ncores;
  size_t start = block * coreid;
  data_t sum;
  for (i0 = start; i0 < (start+block); i0 += blockSize)
    for (k0 = 0; k0 < lda; k0 += blockSize)
    for (j0 = 0; j0 < lda; j0 += blockSize)
        for (i = i0; i < i0 + blockSize; ++i)
          for (j = j0; j < j0 + blockSize; ++j){
            sum = C[i*lda + j];
            for (k = k0; k < k0 + blockSize; ++k)
              sum += A[i*lda + k] * B[k*lda + j];
            C[i*lda + j] = sum;
          }

}
// 2693409
