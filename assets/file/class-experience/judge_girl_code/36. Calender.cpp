# include <stdio.h>
int year, month, week, leap;
int main(){
	scanf("%d %d %d", &year, &month, &week);
	if (month > 12 || week > 6 || month < 1 || week < 0) printf("invalid\n");
	else{
		if(((year % 100 != 0 && year % 4 == 0) || year % 400 == 0) && year != 2000) leap = 1;
		else leap = 0;
		int days = 0;
		switch (month){
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			days += 31;
			break;
			case 4: case 6: case 9: case 11: 
			days += 30;
			break;
			case 2:
			if (leap == 1) days += 29; 
			else days += 28; 
			break; 
		}
		
		printf(" Su Mo Tu We Th Fr Sa\n");
		printf("=====================\n");
		
		int i = 0, count = 1;
		if (week != 0){ 
			for ( i = 0 ; i < week; i++) printf("   ");
			for ( ; i < days + week; i++){
				if (i % 7 == 0) printf("\n");
				printf("%3d", count);
				count++;
			}
		printf("\n");
		}
		else if (week == 0){
			for (i = 1; i <= days; i++){
				printf("%3d", count);
				count++;
				if (days != 28 || i != 28){
					if (i % 7 == 0) printf("\n");
				}
			}
		if ( i % 7 != 0)printf("\n");
		} 
		
		printf("=====================\n");
	}
}
