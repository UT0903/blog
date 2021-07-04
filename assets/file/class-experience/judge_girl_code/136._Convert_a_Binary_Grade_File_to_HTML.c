#include <stdio.h>
#include <assert.h>

typedef struct student{
    char name[20];
    int id;
    char phone[10];
    float grade[4];
    int birth_year;
    int birth_month;
    int birth_day;
} Student;
Student c[1];
char ipfile[80], opfile[80];
int main(){
	scanf("%s %s", ipfile, opfile);
	FILE *fp, *tp;
	fp = fopen(ipfile, "rb");
	assert(fp != NULL);
	tp = fopen(opfile, "w");
	assert(tp != NULL);
	fprintf(tp, "<table border=\"1\">\n");
	fprintf(tp, "<tbody>\n");
	
	int return_num = 0;
	while((return_num = fread(c, sizeof(Student), 1, fp)) != 0){
		//printf("OK\n");
		fprintf(tp, "<tr>\n");
		fprintf(tp, "<td>%s</td>\n", c[0].name);
		fprintf(tp, "<td>%d</td>\n", c[0].id);
		fprintf(tp, "<td>%s</td>\n", c[0].phone);
		fprintf(tp, "<td>%f, %f, %f, %f</td>\n", c[0].grade[0], c[0].grade[1], c[0].grade[2], c[0].grade[3]);
		fprintf(tp, "<td>%d, %d, %d</td>\n", c[0].birth_year, c[0].birth_month, c[0].birth_day);
		fprintf(tp, "</tr>\n");
	}
	
	fprintf(tp, "</tbody>\n");
	fprintf(tp, "</table>\n");
	fclose(fp);
	fclose(tp);
}