# include <stdio.h>

int main(){
	scanf("%d %d", &the_number_of_machine, &the_number_of_job);
	for(i = 1; i <= the_number_of_job; i++){
		scanf("%d %d", &arri_time, &the_number_of_task);
		t[i][0] = arri_time;
		for(j = 1; j <= the_number_of_task; j++){
			scanf("%d %d", &machine, &spend_time);
			t[i][j] = spend_time + t[i][j-1];
			m[i][j] = machine;
		}
	}
	for(job = 1; job <= the_number_of_job; job++){
		if(t[job][task] <= time && ready_job[job] == 1 && ready_machine[machine] == 1){
			ready_job[job] = 0;
			ready_machine[machine] = 0;
		}
	}
	time++;
}
