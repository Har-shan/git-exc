#ifndef STATISTICS_H
#define STATISTICS_H
#include <stdio.h>
#include "students.h"

void processResults(struct Student s[], int n);
void computeClassStatistics(struct Student s[], int n, FILE *fp);


#endif