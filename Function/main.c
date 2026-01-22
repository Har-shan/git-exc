#include <stdio.h>
#include "files.h"
#include "results.h"

#define MAX 100

int main() {
    struct Student students[MAX];
    int count = 0;

    readFromFile(students, &count);

    if (count <= 0)
    {
        printf("No valid student records found.\n");
        return 0;
    }

    processResults(students, count);

        writeToFile(students, count);

    printf(" Check data/result.txt\n");
    return 0;
}
