#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SUBJECTS 5
#define MAX 100

/* ---------- Structure ---------- */
struct Student {
    char id[20];
    char name[30];
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

/* ---------- Function Prototypes ---------- */
int validID(char id[], struct Student s[], int count);
int validName(char name[]);
int validMinor(int m);
int validMajor(int m);
int getGradePoint(int marks);
void getSubjectGrade(int marks, char grade[]);
void calculateResult(struct Student *s);
void assignOverallGrade(struct Student *s);
void displayReport(struct Student s[], int n);
void classStatistics(struct Student s[], int n);

/* ---------- Validation ---------- */
int validID(char id[], struct Student s[], int count) {
    for (int i = 0; id[i] != '\0'; i++)
        if (!isalnum(id[i]))
            return 0;

    for (int i = 0; i < count; i++)
        if (strcmp(id, s[i].id) == 0)
            return 0;

    return 1;
}

int validName(char name[]) {
    for (int i = 0; name[i] != '\0'; i++)
        if (!isalpha(name[i]))
            return 0;
    return 1;
}

int validMinor(int m) {
    return (m >= 0 && m <= 40);
}

int validMajor(int m) {
    return (m >= 0 && m <= 60);
}

/* ---------- Grade Helpers ---------- */
int getGradePoint(int marks) {
    if (marks >= 90) return 10;
    else if (marks >= 85) return 9;
    else if (marks >= 75) return 8;
    else if (marks >= 65) return 7;
    else if (marks >= 60) return 6;
    else if (marks >= 55) return 5;
    else if (marks >= 50) return 4;
    else return 0;
}

void getSubjectGrade(int marks, char grade[]) {
    if (marks >= 90) strcpy(grade, "O");
    else if (marks >= 85) strcpy(grade, "A+");
    else if (marks >= 75) strcpy(grade, "A");
    else if (marks >= 65) strcpy(grade, "B+");
    else if (marks >= 60) strcpy(grade, "B");
    else if (marks >= 55) strcpy(grade, "C");
    else if (marks >= 50) strcpy(grade, "D");
    else strcpy(grade, "F");
}

/* ---------- Computation ---------- */
void calculateResult(struct Student *s) {
    int sumGP = 0;
    s->total = 0;

    for (int i = 0; i < SUBJECTS; i++) {
        s->subjectTotal[i] = s->minor[i] + s->major[i];
        s->total += s->subjectTotal[i];

        getSubjectGrade(s->subjectTotal[i], s->subjectGrade[i]);
        s->gradePoint[i] = getGradePoint(s->subjectTotal[i]);
        sumGP += s->gradePoint[i];
    }

    s->percentage = s->total / 5.0;
    s->cgpa = sumGP / 5.0;
}

void assignOverallGrade(struct Student *s) {
    for (int i = 0; i < SUBJECTS; i++) {
        if (s->subjectTotal[i] < 50) {
            strcpy(s->grade, "F");
            s->cgpa = 0.0;
            return;
        }
    }

    float p = s->percentage;

    if (p >= 90) strcpy(s->grade, "O");
    else if (p >= 85) strcpy(s->grade, "A+");
    else if (p >= 75) strcpy(s->grade, "A");
    else if (p >= 65) strcpy(s->grade, "B+");
    else if (p >= 60) strcpy(s->grade, "B");
    else if (p >= 55) strcpy(s->grade, "C");
    else if (p >= 50) strcpy(s->grade, "D");
    else strcpy(s->grade, "F");
}

/* ---------- Output ---------- */
void displayReport(struct Student s[], int n) {
    printf("\nID        Name     ");
    for (int i = 1; i <= SUBJECTS; i++)
        printf("S%d G%d  ", i, i);
    printf("Total   %%     Grade CGPA\n");

    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%-9s %-8s ", s[i].id, s[i].name);
        for (int j = 0; j < SUBJECTS; j++)
            printf("%2d %-3s ", s[i].subjectTotal[j], s[i].subjectGrade[j]);

        printf("%4d  %6.2f   %-4s %.2f\n",
               s[i].total, s[i].percentage, s[i].grade, s[i].cgpa);
    }
}

void classStatistics(struct Student s[], int n) {
    float sum = 0, max, min;
    int gradeCount[8] = {0};

    max = min = s[0].percentage;

    for (int i = 0; i < n; i++) {
        sum += s[i].percentage;
        if (s[i].percentage > max) max = s[i].percentage;
        if (s[i].percentage < min) min = s[i].percentage;

        if (!strcmp(s[i].grade, "O")) gradeCount[0]++;
        else if (!strcmp(s[i].grade, "A+")) gradeCount[1]++;
        else if (!strcmp(s[i].grade, "A")) gradeCount[2]++;
        else if (!strcmp(s[i].grade, "B+")) gradeCount[3]++;
        else if (!strcmp(s[i].grade, "B")) gradeCount[4]++;
        else if (!strcmp(s[i].grade, "C")) gradeCount[5]++;
        else if (!strcmp(s[i].grade, "D")) gradeCount[6]++;
        else gradeCount[7]++;
    }

    printf("\nClass Average Percentage: %.2f\n", sum / n);
    printf("Highest Percentage: %.2f\n", max);
    printf("Lowest Percentage: %.2f\n", min);
}

/* ---------- Main ---------- */
int main() {
    FILE *fp;
    struct Student s[MAX];
    int n;

    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }

    fscanf(fp, "%d", &n);

    for (int i = 0; i < n; i++) {
        fscanf(fp, "%s %s", s[i].id, s[i].name);

        if (!validID(s[i].id, s, i) || !validName(s[i].name)) {
            printf("Invalid student data.\n");
            return 1;
        }

        for (int j = 0; j < SUBJECTS; j++) {
            fscanf(fp, "%d %d", &s[i].minor[j], &s[i].major[j]);

            if (!validMinor(s[i].minor[j]) || !validMajor(s[i].major[j])) {
                printf("Invalid marks for student %s\n", s[i].id);
                return 1;
            }
        }

        calculateResult(&s[i]);
        assignOverallGrade(&s[i]);
    }

    fclose(fp);

    displayReport(s, n);
    classStatistics(s, n);

    return 0;
}
