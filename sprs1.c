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
int validID(char id[]);
int validName(char name[]);
int validMinor(int m);
int validMajor(int m);
int getGradePoint(int marks);
void getSubjectGrade(int marks, char grade[]);
void inputAndStore(struct Student s[], int n);
void processResults(struct Student s[], int n);
void displayReport(struct Student s[], int n);
void classStatistics(struct Student s[], int n);

/* ---------- Validation ---------- */
int validID(char id[]) {
    for (int i = 0; id[i]; i++)
        if (!isalnum(id[i]))
            return 0;
    return 1;
}

int validName(char name[]) {
    for (int i = 0; name[i]; i++)
        if (!isalpha(name[i]))
            return 0;
    return 1;
}

int validMinor(int m) { return (m >= 0 && m <= 40); }
int validMajor(int m) { return (m >= 0 && m <= 60); }

/* ---------- Grade Helpers ---------- */
int getGradePoint(int m) {
    if (m >= 90) return 10;
    else if (m >= 85) return 9;
    else if (m >= 75) return 8;
    else if (m >= 65) return 7;
    else if (m >= 60) return 6;
    else if (m >= 55) return 5;
    else if (m >= 50) return 4;
    else return 0;
}

void getSubjectGrade(int m, char g[]) {
    if (m >= 90) strcpy(g, "O");
    else if (m >= 85) strcpy(g, "A+");
    else if (m >= 75) strcpy(g, "A");
    else if (m >= 65) strcpy(g, "B+");
    else if (m >= 60) strcpy(g, "B");
    else if (m >= 55) strcpy(g, "C");
    else if (m >= 50) strcpy(g, "D");
    else strcpy(g, "F");
}

/* ---------- Input + Store in File ---------- */
void inputAndStore(struct Student s[], int n) {
    FILE *fp = fopen("students.txt", "w");

    fprintf(fp, "%d\n", n);

    for (int i = 0; i < n; i++) {

        /* ID */
        do {
            printf("Enter ID for student %d: ", i + 1);
            scanf("%s", s[i].id);
        } while (!validID(s[i].id));

        /* Name (with spaces) */
        clearBuffer();
        do {
            printf("Enter Name: ");
            fgets(s[i].name, sizeof(s[i].name), stdin);
            s[i].name[strcspn(s[i].name, "\n")] = '\0';
        } while (!validName(s[i].name));

        fprintf(fp, "%s %s\n", s[i].id, s[i].name);

        /* Marks */
        for (int j = 0; j < SUBJECTS; j++) {
            do {
                printf("Subject %d Minor & Major: ", j + 1);
                scanf("%d %d", &s[i].minor[j], &s[i].major[j]);
            } while (!validMinor(s[i].minor[j]) || !validMajor(s[i].major[j]));

            fprintf(fp, "%d %d\n", s[i].minor[j], s[i].major[j]);
        }
    }

    fclose(fp);
}


/* ---------- Read File & Process ---------- */
void processResults(struct Student s[], int n) {
    FILE *fp = fopen("students.txt", "r");
    fscanf(fp, "%d", &n);

    for (int i = 0; i < n; i++) {
        fscanf(fp, "%s %s", s[i].id, s[i].name);

        s[i].total = 0;
        int sumGP = 0;

        for (int j = 0; j < SUBJECTS; j++) {
            fscanf(fp, "%d %d", &s[i].minor[j], &s[i].major[j]);

            s[i].subjectTotal[j] = s[i].minor[j] + s[i].major[j];
            s[i].total += s[i].subjectTotal[j];

            getSubjectGrade(s[i].subjectTotal[j], s[i].subjectGrade[j]);
            s[i].gradePoint[j] = getGradePoint(s[i].subjectTotal[j]);
            sumGP += s[i].gradePoint[j];
        }

        s[i].percentage = s[i].total / 5.0;
        s[i].cgpa = sumGP / 5.0;

        strcpy(s[i].grade, "F");
        if (s[i].cgpa > 0) {
            if (s[i].percentage >= 90) strcpy(s[i].grade, "O");
            else if (s[i].percentage >= 85) strcpy(s[i].grade, "A+");
            else if (s[i].percentage >= 75) strcpy(s[i].grade, "A");
            else if (s[i].percentage >= 65) strcpy(s[i].grade, "B+");
            else if (s[i].percentage >= 60) strcpy(s[i].grade, "B");
            else if (s[i].percentage >= 55) strcpy(s[i].grade, "C");
            else if (s[i].percentage >= 50) strcpy(s[i].grade, "D");
        }
    }
    fclose(fp);
}

/* ---------- Output ---------- */
void displayReport(struct Student s[], int n) {
    printf("\nID   Name  ");
    for (int i = 1; i <= SUBJECTS; i++)
        printf("S%d G%d ", i, i);
    printf("Total %% Grade CGPA\n");

    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%-4s %-6s ", s[i].id, s[i].name);
        for (int j = 0; j < SUBJECTS; j++)
            printf("%2d %-2s ", s[i].subjectTotal[j], s[i].subjectGrade[j]);
        printf("%4d %6.2f %-4s %.2f\n",
               s[i].total, s[i].percentage, s[i].grade, s[i].cgpa);
    }
}

void classStatistics(struct Student s[], int n) {
    float sum = 0, max = s[0].percentage, min = s[0].percentage;
    for (int i = 0; i < n; i++) {
        sum += s[i].percentage;
        if (s[i].percentage > max) max = s[i].percentage;
        if (s[i].percentage < min) min = s[i].percentage;
    }
    printf("\nClass Avg: %.2f  Highest: %.2f  Lowest: %.2f\n",
           sum / n, max, min);
}

/* ---------- Main ---------- */
int main() {
    struct Student s[MAX];
    int n;

    printf("Enter number of students: ");
    scanf("%d", &n);

    inputAndStore(s, n);
    processResults(s, n);
    displayReport(s, n);
    classStatistics(s, n);

    return 0;
}
