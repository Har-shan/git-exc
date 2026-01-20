#include <stdio.h>
#include <string.h>
#include "Header/files.h"
#include "Header/validation.h"


void readFromFile(struct Student s[], int *n) {
FILE *fp = fopen("data/students.txt", "r");
if (!fp) {
printf("Error: Input file not found.\n");
*n = 0;
return;
}


fscanf(fp, "%d\n", n);


for (int i = 0; i < *n; i++) {
fscanf(fp, "%s", s[i].id);
fgetc(fp);
fgets(s[i].name, 50, fp);
s[i].name[strcspn(s[i].name, "\n")] = '\0';


if (!validID(s[i].id) || !validName(s[i].name)) {
printf("Invalid student data in file.\n");
fclose(fp);
*n = 0;
return;
}


for (int j = 0; j < SUBJECTS; j++) {
fscanf(fp, "%d %d", &s[i].minor[j], &s[i].major[j]);
if (!validMinor(s[i].minor[j]) || !validMajor(s[i].major[j])) {
printf("Invalid marks in file.\n");
fclose(fp);
*n = 0;
return;
}
}
}
fclose(fp);
}


void writeToFile(struct Student s[], int n) {
FILE *fp = fopen("data/result.txt", "w");
if (!fp) {
printf("Error creating output file.\n");
return;
}


fprintf(fp, "ID Name ");
for (int i = 1; i <= SUBJECTS; i++)
fprintf(fp, "S%d G%d ", i, i);
fprintf(fp, "Total %% Grade CGPA\n");
fprintf(fp, "----------------------------------------------------------------------------\n");


for (int i = 0; i < n; i++) {
fprintf(fp, "%-9s %-15s ", s[i].id, s[i].name);
for (int j = 0; j < SUBJECTS; j++)
fprintf(fp, "%2d %-3s ", s[i].subjectTotal[j], s[i].subjectGrade[j]);
fprintf(fp, "%4d %6.2f %-4s %.2f\n",
s[i].total, s[i].percentage, s[i].grade, s[i].cgpa);
}


fclose(fp);
}