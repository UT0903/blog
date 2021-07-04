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
							print[k][0] = '0';  //어쨁 
							print[k][h - 1] = '0'; //어짾 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '0';//そⅹ쨁 
							
							print[(i+1) * w - 2][k] = '0';//そ쩵쨁
							print[i*w][k + (h-1) / 2] = '0';//そⅹ짾 
							print[(i+1) * w - 2][k + (h-1)/2] = '0';//そ쩵짾 
						}
						
							
						break;
					case 1: 
						
						for(k = 1; k < (h-1) / 2; k++){			
							print[(i+1) * w - 2][k] = '1';//そ쩵쨁
							print[(i+1) * w - 2][k + (h-1)/2] = '1';//そ쩵짾 
						}
						break;
					case 2:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '2';  //어쨁 
							print[k][h/2] = '2' ;//어ㄴ 
							print[k][h - 1] = '2'; //어짾 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							
							print[(i+1) * w - 2][k] = '2';//そ쩵쨁
							print[i*w][k + (h-1) / 2] = '2';//そⅹ짾  
						}
						break;
					case 3:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '3';  //어쨁 
							print[k][h/2] = '3' ;//어ㄴ
							print[k][h - 1] = '3'; //어짾 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[(i+1) * w - 2][k] = '3';//そ쩵쨁
							print[(i+1) * w - 2][k + (h-1)/2] = '3';//そ쩵짾 
						}
						break;
					case 4:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][h/2] = '4' ;//어ㄴ
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '4';//そⅹ쨁 
							print[(i+1) * w - 2][k] = '4';//そ쩵쨁
							print[(i+1) * w - 2][k + (h-1)/2] = '4';//そ쩵짾 
						}
						break;
					case 5:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '5';  //어쨁 
							print[k][h/2] = '5' ;//어ㄴ
							print[k][h - 1] = '5'; //어짾 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '5';//そⅹ쨁 
							print[(i+1) * w - 2][k + (h-1)/2] = '5';//そ쩵짾 
						}
						break;
					case 6:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '6';  //어쨁 
							print[k][h/2] = '6' ;//어ㄴ
							print[k][h - 1] = '6'; //어짾 
						}
					
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '6';//そⅹ쨁 
							print[i*w][k + (h-1) / 2] = '6';//そⅹ짾 
							print[(i+1) * w - 2][k + (h-1)/2] = '6';//そ쩵짾 
						}
						break;
					case 7:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '7';  //어쨁 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '7';//そⅹ쨁 
							print[(i+1) * w - 2][k] = '7';//そ쩵쨁
							print[(i+1) * w - 2][k + (h-1)/2] = '7';//そ쩵짾 
						}
						break;
					case 8:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '8';  //어쨁 
							print[k][h/2] = '8' ;//어ㄴ
							print[k][h - 1] = '8'; //어짾 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '8';//そⅹ쨁 
							print[(i+1) * w - 2][k] = '8';//そ쩵쨁
							print[i*w][k + (h-1) / 2] = '8';//そⅹ짾 
							print[(i+1) * w - 2][k + (h-1)/2] = '8';//そ쩵짾 
						}
						break;
					case 9:
						for(k = i * w + 1; k < (i + 1) * w - 2; k++){  
							print[k][0] = '9';  //어쨁 
							print[k][h/2] = '9' ;//어ㄴ 
						}
						
						for(k = 1; k < (h-1) / 2; k++){
							print[i*w][k] = '9';//そⅹ쨁 
							print[(i+1) * w - 2][k] = '9';//そ쩵쨁
							print[(i+1) * w - 2][k + (h-1)/2] = '9';//そ쩵짾 
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
