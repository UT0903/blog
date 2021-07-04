	#include <stdio.h>
	#include <stdlib.h>
	
	int x_parking_lot[10], y_parking_lot[10], space_parking_lot[10], n, x_bike[100000], y_bike[100000], i, j, a = 0, b = 0, dis[100000][10], nearest,full[10],m,bike_in_parking_lot[10];
	int main()
	{
		scanf("%d", &n);
		for(i = 0 ;i < n ;i++){
			scanf("%d %d %d", &x_parking_lot[i], &y_parking_lot[i], &space_parking_lot[i]);
			if(space_parking_lot[i] == 0) full[i] = 1;
		}
		scanf("%d", &m);
		for(j = 0; j < m; j++){
			scanf("%d %d", &x_bike[j], &y_bike[j]);
		}
		for(j = 0; j < m; j++){
			for(i = 0 ; i < n ; i++) {
				if(!full[i]) {
					dis[j][i] = abs(x_parking_lot[i] - x_bike[j]) + abs(y_parking_lot[i] - y_bike[j]);
					nearest = i;
					break;
				}
			} 
			i++;
			for( ; i < n; i++){
				if(full[i]) continue;
				dis[j][i] = abs(x_parking_lot[i] - x_bike[j]) + abs(y_parking_lot[i] - y_bike[j]);
				if (dis[j][i] < dis[j][nearest]){
					if(!full[i])
						nearest = i;
				}
				if (dis[j][nearest] == dis[j][i]){
					if(!full[i]){
						if (x_parking_lot[i] < x_parking_lot[nearest])
							nearest = i;
						else if(x_parking_lot[i] == x_parking_lot[nearest] && y_parking_lot[i] < y_parking_lot[nearest])
							nearest = i;
					}
				}
			}
			bike_in_parking_lot[nearest] += 1;
			if (bike_in_parking_lot[nearest] == space_parking_lot[nearest]){
				full[nearest] = 1;
			}
		}
		for(i = 0; i < n ; i++){
			printf("%d\n",bike_in_parking_lot[i]);
		}
	 } 
