# include <stdio.h>
# include <string.h>
char a[10];
char print[100][20];

int i = 0, count = 0, x = 0, k, j;
int w, h;
int main(){
	while(scanf("%s", a) != EOF){
		for(i = 0; i < 100; i++){
			for(j = 0; j < 20; j++){
				print[i][j]=' ';
			}
		}
		scanf("%d %d", &w, &h);
		//printf("%d %d\n",w, h);
		for(i = 0; i < strlen(a); i++){
			//for(j = i * w; j < (i + 1) * w; j++){
				switch(a[i] - 48){
					case 0:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '0';  //��W 
							print[k][h - 1] = '0'; //��U 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '0';//�����W 
							
							print[(i+1) * w - 2][k] = '0';//���k�W
							print[i*w][k + (h-1) / 2] = '0';//�����U 
							print[(i+1) * w - 2][k + (h-1)/2] = '0';//���k�U 
						}
						
							
						break;
					case 1: 
						
						for(k = 1; k < (h-1) / 2; k++){			
							print[(i+1) * w - 2][k] = '1';//���k�W
							print[(i+1) * w - 2][k + (h-1)/2] = '1';//���k�U 
						}
						break;
					case 2:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '2';  //��W 
							print[k][h/2] = '2' ;//� 
							print[k][h - 1] = '2'; //��U 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							
							print[(i+1) * w - 2][k] = '2';//���k�W
							print[i*w][k + (h-1) / 2] = '2';//�����U  
						}
						break;
					case 3:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '3';  //��W 
							print[k][h/2] = '3' ;//�
							print[k][h - 1] = '3'; //��U 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[(i+1) * w - 2][k] = '3';//���k�W
							print[(i+1) * w - 2][k + (h-1)/2] = '3';//���k�U 
						}
						break;
					case 4:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][h/2] = '4' ;//�
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '4';//�����W 
							print[(i+1) * w - 2][k] = '4';//���k�W
							print[(i+1) * w - 2][k + (h-1)/2] = '4';//���k�U 
						}
						break;
					case 5:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '5';  //��W 
							print[k][h/2] = '5' ;//�
							print[k][h - 1] = '5'; //��U 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '5';//�����W 
							print[(i+1) * w - 2][k + (h-1)/2] = '5';//���k�U 
						}
						break;
					case 6:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '6';  //��W 
							print[k][h/2] = '6' ;//�
							print[k][h - 1] = '6'; //��U 
						}
					
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '6';//�����W 
							print[i*w][k + (h-1) / 2] = '6';//�����U 
							print[(i+1) * w - 2][k + (h-1)/2] = '6';//���k�U 
						}
						break;
					case 7:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '7';  //��W 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '7';//�����W 
							print[(i+1) * w - 2][k] = '7';//���k�W
							print[(i+1) * w - 2][k + (h-1)/2] = '7';//���k�U 
						}
						break;
					case 8:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '8';  //��W 
							print[k][h/2] = '8' ;//�
							print[k][h - 1] = '8'; //��U 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '8';//�����W 
							print[(i+1) * w - 2][k] = '8';//���k�W
							print[i*w][k + (h-1) / 2] = '8';//�����U 
							print[(i+1) * w - 2][k + (h-1)/2] = '8';//���k�U 
						}
						break;
					case 9:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '9';  //��W 
							print[k][h/2] = '9' ;//� 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '9';//�����W 
							print[(i+1) * w - 2][k] = '9';//���k�W
							print[(i+1) * w - 2][k + (h-1)/2] = '9';//���k�U 
						}
						break;	
				}
			//}
				
		}
		for(j = 0; j < h; j++){
			for(i = 0; i < strlen(a) * w; i++){
				printf("%c", print[i][j]);
			}
			printf("\n");
		}
		
		for(i = 0; i < 100; i++){
			for(j = 0; j < 20; j++){
				print[i][j] = ' ';
			}
		}
		for(i = 0; i < 10; i++){
			a[i] = ' ';
		}	
		x = 0;
				
			
		
		
	}
}
