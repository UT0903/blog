# include <stdio.h>

int year, first, n ,leap;
int main (){
	scanf("%d %d %d", &year, &first, &n);
		int month, day, i;
		for (i = 0; i < n; i++){
			int sum = 0;
			scanf("%d %d", &month , &day);
			if (year != 2000  && (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))) leap = 1;
			else {
				leap = 0;
				}
			if (month > 12 || month < 1) printf("-1\n");
			else if (day > 31 || (month == 4 && day == 31)|| (month == 6 && day == 31)|| (month == 9 && day == 31)|| (month == 11 && day == 31)||(month == 2 && day > 28 && leap == 0)||(month == 2 && day > 29 && leap == 1) || day < 1) printf("-2\n");
			else{
				
				sum = day;
				if (month > 1){
					if (month > 2){
						if (month > 3){
							if (month > 4){
								if (month > 5){
									if (month > 6){
										if (month > 7){
											if (month > 8){
												if (month > 9){
													if (month > 10){
														if (month > 11){
														sum += 30;	
														}
														sum += 31;
													}
													sum += 30;
												}
												sum += 31;
											}
											sum += 31;
										}
										sum += 30;
									}
									sum += 31;
								}
								sum += 30;
							}
							sum += 31;
						}
						sum += 28;
					}
					sum += 31;
				}
				sum += first;
				
				sum--;
				
				if (month > 2 ){
					sum += leap;
				}
				sum = sum % 7; 
				printf("%d\n", sum);
			}
		}

}

