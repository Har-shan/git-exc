#include <string.h>
#include "Header/results.h"
#include "Header/grades.h"

void processResults(struct Student s[], int n) {
for (int i = 0; i < n; i++) {
int sumGP = 0, fail = 0;
s[i].total = 0;


for (int j = 0; j < SUBJECTS; j++) {
s[i].subjectTotal[j] = s[i].minor[j] + s[i].major[j];
s[i].total += s[i].subjectTotal[j];


getSubjectGrade(s[i].subjectTotal[j], s[i].subjectGrade[j]);
s[i].gradePoint[j] = getGradePoint(s[i].subjectTotal[j]);
sumGP += s[i].gradePoint[j];


if (s[i].subjectTotal[j] < 50) fail = 1;
}


s[i].percentage = s[i].total / 5.0;
s[i].cgpa = fail ? 0.0 : sumGP / 5.0;


if (fail) strcpy(s[i].grade, "F");
else if (s[i].percentage >= 90) strcpy(s[i].grade, "O");
else if (s[i].percentage >= 85) strcpy(s[i].grade, "A+");
else if (s[i].percentage >= 75) strcpy(s[i].grade, "A");
else if (s[i].percentage >= 65) strcpy(s[i].grade, "B+");
else if (s[i].percentage >= 60) strcpy(s[i].grade, "B");
else if (s[i].percentage >= 55) strcpy(s[i].grade, "C");
else if (s[i].percentage >= 50) strcpy(s[i].grade, "D");
else strcpy(s[i].grade, "F");
}
}


void computeClassStatistics(struct Student s[], int n, FILE *fp) {
float sum = 0, highest, lowest;
int gradeCount[8] = {0};


highest = lowest = s[0].percentage;


for (int i = 0; i < n; i++) {
sum += s[i].percentage;
if (s[i].percentage > highest) highest = s[i].percentage;
if (s[i].percentage < lowest) lowest = s[i].percentage;


if (!strcmp(s[i].grade, "O")) gradeCount[0]++;
else if (!strcmp(s[i].grade, "A+")) gradeCount[1]++;
else if (!strcmp(s[i].grade, "A")) gradeCount[2]++;
else if (!strcmp(s[i].grade, "B+")) gradeCount[3]++;
else if (!strcmp(s[i].grade, "B")) gradeCount[4]++;
else if (!strcmp(s[i].grade, "C")) gradeCount[5]++;
else if (!strcmp(s[i].grade, "D")) gradeCount[6]++;
else gradeCount[7]++;
}


fprintf(fp, "\n--- Class Statistics ---\n");
fprintf(fp, "Class Average Percentage : %.2f\n", sum / n);
fprintf(fp, "Highest Percentage : %.2f\n", highest);
fprintf(fp, "Lowest Percentage : %.2f\n", lowest);


fprintf(fp, "\nGrade Distribution:\n");
fprintf(fp, "O : %d\n", gradeCount[0]);
fprintf(fp, "A+ : %d\n", gradeCount[1]);
fprintf(fp, "A : %d\n", gradeCount[2]);
fprintf(fp, "B+ : %d\n", gradeCount[3]);
fprintf(fp, "B : %d\n", gradeCount[4]);
fprintf(fp, "C : %d\n", gradeCount[5]);
fprintf(fp, "D : %d\n", gradeCount[6]);
fprintf(fp, "F : %d\n", gradeCount[7]);
}