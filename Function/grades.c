#include <string.h>
#include "grades.h"

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
