# include <stdio.h>
typedef struct{
    int rawScore;
    double scaledScore;
}Score;
 
typedef struct{
    char id[10];
    Score score[18];
    double finalScore;
}Student;
 
typedef struct{
    int numStudent;
    Student student[1000];
}Classes;

void computeGrade(Classes classes[2]){
	for(int k = 0; k < 18; k++){
		double ave[2] = {0, 0};
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < classes[i].numStudent; j++){
				ave[i] += classes[i].student[j].score[k].rawScore;
			}
			ave[i] /= classes[i].numStudent;
		}
		if(ave[0] > ave[1]){
			double ratio = ave[0] / ave[1];
			for(int j = 0; j < classes[1].numStudent; j++){
				if(classes[1].student[j].score[k].rawScore * ratio > 100){
					classes[1].student[j].score[k].scaledScore = 100;
				}
				else{
					classes[1].student[j].score[k].scaledScore = classes[1].student[j].score[k].rawScore * ratio;
				}
				//printf("classes[1].student[%d].score[%d].scaledScore = %f\n", j, k, classes[1].student[j].score[k].scaledScore);
				
			}
			for(int j = 0; j < classes[0].numStudent; j++){
				classes[0].student[j].score[k].scaledScore = classes[0].student[j].score[k].rawScore;
			}
		}
		else{
			double ratio = ave[1] / ave[0];
			for(int j = 0; j < classes[0].numStudent; j++){
				if(classes[0].student[j].score[k].rawScore * ratio > 100){
					classes[0].student[j].score[k].scaledScore = 100;
				}
				else{
					classes[0].student[j].score[k].scaledScore = classes[0].student[j].score[k].rawScore * ratio;
				}
				//printf("classes[0].student[%d].score[%d].scaledScore = %f\n", j, k, classes[0].student[j].score[k].scaledScore);
			}
			for(int j = 0; j < classes[1].numStudent; j++){
				classes[1].student[j].score[k].scaledScore = classes[1].student[j].score[k].rawScore;
			}
		}
	}
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < classes[i].numStudent; j++){
			for(int k = 0; k < 18; k++){
				classes[i].student[j].finalScore += classes[i].student[j].score[k].scaledScore;
			}
			classes[i].student[j].finalScore *= 0.06;
			if(classes[i].student[j].finalScore > 100){
				classes[i].student[j].finalScore = 100;
			}
			printf("%s %f\n", classes[i].student[j].id, classes[i].student[j].finalScore);
		}
	}

}

//#include <stdio.h>
//#include "computeGrade.h"
 
int main()
{
    Classes classes[2];
    scanf("%d", &classes[0].numStudent);
    for (int i = 0; i < classes[0].numStudent; i++) {
        scanf("%s", classes[0].student[i].id);
        for (int j = 0; j < 18; j++) {
            scanf("%d", &classes[0].student[i].score[j].rawScore);
        }
    }
    scanf("%d", &classes[1].numStudent);
    for (int i = 0; i < classes[1].numStudent; i++) {
        scanf("%s", classes[1].student[i].id);
        for (int j = 0; j < 18; j++) {
            scanf("%d", &classes[1].student[i].score[j].rawScore);
        }
    }
    computeGrade(classes);
    return 0;
}