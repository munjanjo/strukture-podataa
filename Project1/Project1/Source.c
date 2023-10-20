#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#define MAX_SIZE 50
#define MAX_LINE 1024

typedef struct _student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int points;
}Student;
int main() {
	int noRows = 0;
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };
	filePointer = fopen("l.txt.txt", "r");
	if (!filePointer) {
		printf("klrivo");
		return -1;

	}
	while (!feof(filePointer)) {
		fgets(buffer, MAX_LINE, filePointer);
		noRows++;


	}
	rewind(filePointer);
	Student* stud = NULL;
	stud = (Student *)malloc(noRows * sizeof(Student));
	for (int i = 0; i < noRows; i++) {
		fscanf(filePointer, "%s %s %d\n", stud[i].name, stud[i].surname, &stud[i].points);
	
	}
	
	double prosjek=0;
	for (int i = 0; i < noRows; i++) {
		prosjek = (double)stud[i].points / 50 * 100;
		printf("%s %s %d %.2lf %\n", stud[i].name, stud[i].surname, stud[i].points, prosjek);
	}
	
	fclose(filePointer);
	return 0;

}
