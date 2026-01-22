#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SUBJECTS 5
#define MAX 100
#define GRADES 8

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

int validID(char id[]) {
    for (int i = 0; id[i]; i++)
        if (!isalnum(id[i]))
            return 0;
    return 1;
}

int validName(char name[]) {
    for (int i = 0; name[i]; i++)
        if (!isalpha(name[i]) && name[i] != ' ')
            return 0;
    return 1;
}

int validMinor(int m) { return (m >= 0 && m <= 40); }
int validMajor(int m) { return (m >= 0 && m <= 60); }

int getGradePoint(int m)
{
    if (m >= 90)
        return 10;
    else if (m >= 85)
        return 9;
    else if (m >= 75)
        return 8;
    else if (m >= 65)
        return 7;
    else if (m >= 60)
        return 6;
    else if (m >= 55)
        return 5;
    else if (m >= 50)
        return 4;
    else
        return 0;
}

void getSubjectGrade(int m, char g[])
{
    if (m >= 90)
        strcpy(g, "O");
    else if (m >= 85)
        strcpy(g, "A+");
    else if (m >= 75)
        strcpy(g, "A");
    else if (m >= 65)
        strcpy(g, "B+");
    else if (m >= 60)
        strcpy(g, "B");
    else if (m >= 55)
        strcpy(g, "C");
    else if (m >= 50)
        strcpy(g, "D");
    else
        strcpy(g, "F");
}

void readFromFile(struct Student s[], int *n)
{
    FILE *fp = fopen("students.txt", "r");
    if (!fp)
    {
        printf("Error: Input file not found.\n");
        return;
    }

    fscanf(fp, "%d\n", n);

    for (int i = 0; i < *n; i++)
    {
        fscanf(fp, "%s", s[i].id);
        fgetc(fp);
        fgets(s[i].name, 50, fp);
        s[i].name[strcspn(s[i].name, "\n")] = '\0';

        if (!validID(s[i].id) || !validName(s[i].name))
        {
            printf("Invalid student data\n");
            fclose(fp);
            return;
        }

        for (int j = 0; j < SUBJECTS; j++)
        {
            fscanf(fp, "%d %d", &s[i].minor[j], &s[i].major[j]);

            if (!validMinor(s[i].minor[j]) || !validMajor(s[i].major[j]))
            {
                printf("Invalid marks.\n");
                fclose(fp);
                return;
            }
        }
    }
    fclose(fp);
}

void processResults(struct Student s[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int sumGP = 0, fail = 0;
        s[i].total = 0;

        for (int j = 0; j < SUBJECTS; j++)
        {
            s[i].subjectTotal[j] = s[i].minor[j] + s[i].major[j];
            s[i].total += s[i].subjectTotal[j];

            getSubjectGrade(s[i].subjectTotal[j], s[i].subjectGrade[j]);
            s[i].gradePoint[j] = getGradePoint(s[i].subjectTotal[j]);
            sumGP += s[i].gradePoint[j];

            if (s[i].subjectTotal[j] < 50)
                fail = 1;
        }

        s[i].percentage = s[i].total / 5.0;
        s[i].cgpa = fail ? 0.0 : sumGP / 5.0;

        if (fail)
            strcpy(s[i].grade, "F");
        else if (s[i].percentage >= 90)
            strcpy(s[i].grade, "O");
        else if (s[i].percentage >= 85)
            strcpy(s[i].grade, "A+");
        else if (s[i].percentage >= 75)
            strcpy(s[i].grade, "A");
        else if (s[i].percentage >= 65)
            strcpy(s[i].grade, "B+");
        else if (s[i].percentage >= 60)
            strcpy(s[i].grade, "B");
        else if (s[i].percentage >= 55)
            strcpy(s[i].grade, "C");
        else if (s[i].percentage >= 50)
            strcpy(s[i].grade, "D");
        else
            strcpy(s[i].grade, "F");
    }
}

void computeClassStatistics(struct Student s[], int n, FILE *fp)
{
    float sum = 0, highest, lowest;
    int gradeCount[GRADES] = {0};

    highest = lowest = s[0].percentage;

    for (int i = 0; i < n; i++)
    {
        sum += s[i].percentage;
        if (s[i].percentage > highest)
            highest = s[i].percentage;
        if (s[i].percentage < lowest)
            lowest = s[i].percentage;

        if (!strcmp(s[i].grade, "O"))
            gradeCount[0]++;
        else if (!strcmp(s[i].grade, "A+"))
            gradeCount[1]++;
        else if (!strcmp(s[i].grade, "A"))
            gradeCount[2]++;
        else if (!strcmp(s[i].grade, "B+"))
            gradeCount[3]++;
        else if (!strcmp(s[i].grade, "B"))
            gradeCount[4]++;
        else if (!strcmp(s[i].grade, "C"))
            gradeCount[5]++;
        else if (!strcmp(s[i].grade, "D"))
            gradeCount[6]++;
        else
            gradeCount[7]++;
    }
    fprintf(fp, "\n");
    fprintf(fp, "Class Average Percentage : %.2f\n", sum / n);
    fprintf(fp, "Highest Percentage       : %.2f\n", highest);
    fprintf(fp, "Lowest Percentage        : %.2f\n", lowest);

    fprintf(fp, "\nNumber of students in each grade category:\n");
    fprintf(fp, "O  : %d\n", gradeCount[0]);
    fprintf(fp, "A+ : %d\n", gradeCount[1]);
    fprintf(fp, "A  : %d\n", gradeCount[2]);
    fprintf(fp, "B+ : %d\n", gradeCount[3]);
    fprintf(fp, "B  : %d\n", gradeCount[4]);
    fprintf(fp, "C  : %d\n", gradeCount[5]);
    fprintf(fp, "D  : %d\n", gradeCount[6]);
    fprintf(fp, "F  : %d\n", gradeCount[7]);
}

void writeToFile(struct Student s[], int n)
{
    FILE *fp = fopen("result.txt", "w");
    if (!fp)
    {
        printf("Error creating output file.\n");
        return;
    }

    fprintf(fp, "ID        Name            ");
    for (int i = 1; i <= SUBJECTS; i++)
        fprintf(fp, "S%d  G%d  ", i, i);
    fprintf(fp, "Total   %%     Grade CGPA\n");

    fprintf(fp, "----------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%-9s %-15s ", s[i].id, s[i].name);
        for (int j = 0; j < SUBJECTS; j++)
            fprintf(fp, "%2d %-3s ", s[i].subjectTotal[j], s[i].subjectGrade[j]);

        fprintf(fp, "%4d  %6.2f   %-4s %.2f\n",
                s[i].total, s[i].percentage, s[i].grade, s[i].cgpa);
    }

    computeClassStatistics(s, n, fp);
    fclose(fp);
}

int main() {
    struct Student s[MAX];
    int n;

    readFromFile(s, &n);
    processResults(s, n);
    writeToFile(s, n);

    printf("Check result.txt file.\n");
    return 0;
}
