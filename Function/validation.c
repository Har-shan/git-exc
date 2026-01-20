#include <ctype.h>
#include <string.h>
#include "Header/validation.h"


int validID(char id[]) {
for (int i = 0; id[i]; i++)
if (!isalnum(id[i])) return 0;
return 1;
}


int validName(char name[]) {
for (int i = 0; name[i]; i++)
if (!isalpha(name[i]) && name[i] != ' ') return 0;
return 1;
}


int validMinor(int m) { return (m >= 0 && m <= 40); }
int validMajor(int m) { return (m >= 0 && m <= 60); }