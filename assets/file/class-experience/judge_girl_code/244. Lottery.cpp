# include <stdio.h>

int main(){
	int spe1, spe2, spe3, fir1, fir2, fir3, n, money = 0;
	scanf("%d %d %d %d %d %d", &spe1, &spe2, &spe3, &fir1, &fir2, &fir3);
	while(scanf("%d", &n) != EOF){
		money += (n == spe1)? 2000000 : 0;
		money += (n == spe2)? 2000000 : 0;
		money += (n == spe3)? 2000000 : 0;
		int m, l;
		m = n;
		l = n;
		int fir1c, fir2c, fir3c;
		if (fir1 % 10 == n % 10){
			fir1c = fir1 / 10;
			n = n / 10;
			if (fir1c % 10 == n % 10){
				fir1c = fir1c / 10;
				n = n / 10;
				if (fir1c % 10 == n % 10){
					fir1c = fir1c / 10;
					n = n / 10;
					money += 200;
					if (fir1c % 10 == n % 10){
						fir1c = fir1c / 10;
						n = n / 10;
						money += 800;
						if (fir1c % 10 == n % 10){
							fir1c = fir1c / 10;
							n = n / 10;
							money += 3000;
							if (fir1c % 10 == n % 10){
								fir1c = fir1c / 10;
								n = n / 10;
								money += 6000;
								if (fir1c % 10 == n % 10){
									fir1c = fir1c / 10;
									n = n / 10;
									money += 30000;
									if (fir1c % 10 == n % 10){
										money += 160000;
									}
								}
							}
						}
					}
				}
			}
		}
		if (fir2 % 10 == n % 10){
			fir2c = fir2 / 10;
			m = m / 10;
			if (fir2c % 10 == m % 10){
				fir2c = fir2c / 10;
				m = m / 10;
				if (fir2c % 10 == m % 10){
					fir2c = fir2c / 10;
					m = m / 10;
					money += 200;
					if (fir2c % 10 == m % 10){
						fir2c = fir2c / 10;
						m = m / 10;
						money += 800;
						if (fir2c % 10 == m % 10){
							fir2c = fir2c / 10;
							m = m / 10;
							money += 3000;
							if (fir2c % 10 == m % 10){
								fir2c = fir2c / 10;
								m = m / 10;
								money += 6000;
								if (fir2c % 10 == m % 10){
									fir2c = fir2c / 10;
									m = m / 10;
									money += 30000;
									if (fir2c % 10 == m % 10){
										money += 160000;
									}
								}
							}
						}
					}
				}
			}
		}
		if (fir3 % 10 == l % 10){
			fir3 = fir3 / 10;
			l = l / 10;
			if (fir3 % 10 == l % 10){
				fir3 = fir3 / 10;
				l = l / 10;
				if (fir3 % 10 == l % 10){
					fir3 = fir3 / 10;
					l = l / 10;
					money += 200;
					if (fir3 % 10 == l % 10){
						fir3 = fir3 / 10;
						l = l / 10;
						money += 800;
						if (fir3 % 10 == l % 10){
							fir3 = fir3 / 10;
							l = l / 10;
							money += 3000;
							if (fir3 % 10 == l % 10){
								fir3 = fir3 / 10;
								l = l / 10;
								money += 6000;
								if (fir3 % 10 == l % 10){
									fir3 = fir3 / 10;
									l = l / 10;
									money += 30000;
									if (fir3 % 10 == l % 10){
										money += 160000;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	printf("%d", money);
}
