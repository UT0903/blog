//#ifndef BOOK_H
//#define BOOK_H
#include <stdio.h> 
#include <string.h>
enum Type {NOVEL, COMICS, MANUAL, TEXTBOOK};
 
struct Book {
    char title[128];
    enum Type type;
    char ISBN[128];
    char authors[128];
    unsigned int importance;
};
 
//#endif

//#ifndef DATE_H
//#define DATE_H
 
struct Date {
    unsigned int year;
    unsigned int month;
    unsigned int day;
};
 
//#endif

#include <stdio.h>
//#include "book.h"
//#include "date.h"
int Compute_days(struct Date date_borrowed, struct Date date_returned){
	int y2, m2, d2;
	int y1, m1, d1;
	
	m1 = (date_borrowed.month + 9) % 12;
	y1 = date_borrowed.year - m1/10;
	d1 = 365*y1 + y1/4 - y1/100 + y1/400 + (m1*306 + 5)/10 + (date_borrowed.day - 1);
 
	m2 = (date_returned.month + 9) % 12;
	y2 = date_returned.year - m2/10;
	d2 = 365*y2 + y2/4 - y2/100 + y2/400 + (m2*306 + 5)/10 + (date_returned.day - 1);
	
	return (d2 - d1 + 1);
}
int Allowdays(struct Book book){
	if(book.type == 0) return 90;
	else if (book.type == 1) return 10;
	else if (book.type == 2) return 100;
	else if (book.type == 3) return 5;
}
int Distance(struct Book book){
	int one[2] = {0, 0};
	int k = 0;
	for(int i = 0; i < 32; i++){
		if((book.importance >> i & (unsigned int)1) == 1){
			one[k] = i;
			k++;
		}
	}
	return (one[1] - one[0] - 1);
}
unsigned int library_fine(struct Book book, struct Date date_borrowed, struct Date date_returned){
	int days = Compute_days(date_borrowed, date_returned);
	int allowdays = Allowdays(book);
	//printf("days = %d\n", days);
	int distance = Distance(book);
	if(days - allowdays <= 0) return 0;
	//printf("allowdays = %d\n", allowdays);
	//printf("distance = %d\n", distance);
	return ((days - allowdays) * distance);
}
 
int main(){
    struct Book book = {
        "Neon Genesis Evangelion",
        COMICS,
        "978-159-116-400-5",
        "Yoshiyuki Sadamoto",
        17
    };
    struct Date date_borrowed, date_returned;
    date_borrowed.year  = 2007;
    date_borrowed.month = 12;
    date_borrowed.day   = 29;
    date_returned.year  = 2008;
    date_returned.month = 1;
    date_returned.day   = 2;
    printf("The fine is $%d.\n", library_fine(book, date_borrowed, date_returned));
    return 0;
}
/*2007 12 29
2008 1 2*/