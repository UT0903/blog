# include <stdio.h>
void snake(const int *ptr_array[100][100], int m){
	int const *buffer[10000] = {0};
	int i, j, k = 0;
	for(i = 0; i < m; i++){
		for(j = 0; j < m; j++){
			buffer[k] = ptr_array[i][j];
			k++;
		}
	}
	//for(i = 0; i < m*m; i++) printf("%d ", *buffer[i]);
//	printf("\n");
	//printf("OK1");
	int const *temp;
	for(i = 0; i < m * m; i++){
		for(j = 0; j < m * m - i; j++){
			if(j + 1 < m * m){
				if(*buffer[j] > *buffer[j + 1]){
					temp = buffer[j + 1];
					buffer[j + 1] = buffer[j];
					buffer[j] = temp;
					//for(k = 0; k < m*m; k++) printf("%d ", *buffer[k]);
					//printf("\n");
				}
			}
			//printf("\n");
		}
	}
	//printf("OK1\n");
	k = 0;
	for(i = 0; i < m; i++){
		if(i % 2 == 0){
			for(j = 0; j < m; j++){
				ptr_array[i][j] = buffer[k];
				k++;
			}
		}
		else if(i % 2 == 1){
			for(j = m - 1; j >= 0; j--){
				ptr_array[i][j] = buffer[k];
				k++;
			}
		}
	}
}

#include <stdio.h>
#include <assert.h>
 
int main()
{
  int array[100][100], check[100][100];
  const int *ptr_array[100][100];
  int i, j, m;
 
  scanf("%d", &m);
  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++) {
      ptr_array[i][j] = &(array[i][j]);
      scanf("%d", &(array[i][j]));
      check[i][j] = array[i][j];
    }
 
  snake(ptr_array, m);
 
  for (i = 0; i < m; i++) {
    for (j = 0; j < m; j++) {
      assert(check[i][j] == array[i][j]);
      assert((ptr_array[i][j] >= &array[0][0]) && (ptr_array[i][j] <= &array[99][99]));
      printf("%d ", *(ptr_array[i][j]));
    }
    printf("\n");
  }
 
  return 0;
}
