#include <stdio.h>
#include "Header/files.h"
#include "Header/results.h"


#define MAX 100


int main() {
struct Student students[MAX];
int count = 0;


readFromFile(students, &count);


if (count <= 0) {
printf("No valid student records found.\n");
return 0;
}


processResults(students, count);


FILE *fp = fopen("data/result.txt", "a");
if (fp) {
computeClassStatistics(students, count, fp);
fclose(fp);
}


printf("Result processing completed. Check data->result.txt\n");
return 0;
}