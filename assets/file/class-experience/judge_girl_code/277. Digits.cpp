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
							print[k][0] = '0';  //橫上 
							print[k][h - 1] = '0'; //橫下 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '0';//直左上 
							
							print[(i+1) * w - 2][k] = '0';//直右上
							print[i*w][k + (h-1) / 2] = '0';//直左下 
							print[(i+1) * w - 2][k + (h-1)/2] = '0';//直右下 
						}
						
							
						break;
					case 1: 
						
						for(k = 1; k < (h-1) / 2; k++){			
							print[(i+1) * w - 2][k] = '1';//直右上
							print[(i+1) * w - 2][k + (h-1)/2] = '1';//直右下 
						}
						break;
					case 2:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '2';  //橫上 
							print[k][h/2] = '2' ;//橫中 
							print[k][h - 1] = '2'; //橫下 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							
							print[(i+1) * w - 2][k] = '2';//直右上
							print[i*w][k + (h-1) / 2] = '2';//直左下  
						}
						break;
					case 3:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '3';  //橫上 
							print[k][h/2] = '3' ;//橫中
							print[k][h - 1] = '3'; //橫下 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[(i+1) * w - 2][k] = '3';//直右上
							print[(i+1) * w - 2][k + (h-1)/2] = '3';//直右下 
						}
						break;
					case 4:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][h/2] = '4' ;//橫中
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '4';//直左上 
							print[(i+1) * w - 2][k] = '4';//直右上
							print[(i+1) * w - 2][k + (h-1)/2] = '4';//直右下 
						}
						break;
					case 5:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '5';  //橫上 
							print[k][h/2] = '5' ;//橫中
							print[k][h - 1] = '5'; //橫下 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '5';//直左上 
							print[(i+1) * w - 2][k + (h-1)/2] = '5';//直右下 
						}
						break;
					case 6:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '6';  //橫上 
							print[k][h/2] = '6' ;//橫中
							print[k][h - 1] = '6'; //橫下 
						}
					
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '6';//直左上 
							print[i*w][k + (h-1) / 2] = '6';//直左下 
							print[(i+1) * w - 2][k + (h-1)/2] = '6';//直右下 
						}
						break;
					case 7:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '7';  //橫上 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '7';//直左上 
							print[(i+1) * w - 2][k] = '7';//直右上
							print[(i+1) * w - 2][k + (h-1)/2] = '7';//直右下 
						}
						break;
					case 8:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '8';  //橫上 
							print[k][h/2] = '8' ;//橫中
							print[k][h - 1] = '8'; //橫下 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '8';//直左上 
							print[(i+1) * w - 2][k] = '8';//直右上
							print[i*w][k + (h-1) / 2] = '8';//直左下 
							print[(i+1) * w - 2][k + (h-1)/2] = '8';//直右下 
						}
						break;
					case 9:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '9';  //橫上 
							print[k][h/2] = '9' ;//橫中 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '9';//直左上 
							print[(i+1) * w - 2][k] = '9';//直右上
							print[(i+1) * w - 2][k + (h-1)/2] = '9';//直右下 
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
