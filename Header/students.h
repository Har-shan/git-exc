#ifndef STUDENT_H
#define STUDENT_H

#define SUBJECTS 5

struct Student {
char id[20];
char name[50];
int minor[SUBJECTS];
int major[SUBJECTS];
int subjectTotal[SUBJECTS];
char subjectGrade[SUBJECTS][3];
int gradePoint[SUBJECTS];
int total;
float percentage;
char grade[3];
float cgpa;
};

#endif