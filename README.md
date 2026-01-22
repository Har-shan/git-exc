# Student Result Processing System (Modular C Project)


The system is designed according to the assignment requirements with:

* Modular programming (multiple source and header files)
* File-based input and output
* Low coupling and high cohesion
* Proper documentation and test plan

---

##  Project Folder Structure

```
GIT-EXC/
│
├── Header/
│   ├── students.h
│   ├── validation.h
│   ├── grades.h
│   ├── files.h
│   └── results.h
│
├── Function/
│   ├── validation.c
│   ├── grades.c
│   ├── file.c
│   ├── results.c
│   └── main.c
│
├── data/
│   ├── students.txt     (input file)
│   └── result.txt       (generated output file)
│
├── docs/
│   ├── Module_Specification.md
│   └── Test_Plan.md
│
└── README.md
```

---

##  Input File Format (`data/students.txt`)

The input file must follow this exact format:

```
N
StudentID Full Name
Minor1 Major1
Minor2 Major2
Minor3 Major3
Minor4 Major4
Minor5 Major5
(repeat for N students)
```

### Example:

```
3
25MCMT03 Harshan
35 40
38 40
42 45
30 42
36 55
25MCMt13 Rigved
25 30
30 30
40 40
35 30
32 35
25MCMT42 Raja
40 53
38 52
45 53
42 45
44 55
```

---

##  Output File (`data/result.txt`)

The output file contains:

* Student-wise details (subject totals and grades)
* Total marks and percentage
* Overall grade and CGPA
* Class statistics:

  * Class average percentage
  * Highest percentage
  * Lowest percentage
  * Number of students in each grade category

### Output Format (Sample):

```
ID        Name            S1  G1  S2  G2  S3  G3  S4  G4  S5  G5  Total   %     Grade CGPA
----------------------------------------------------------------------------
25MCMT03  Harshan         75 A   78 A   87 A+  72 B+  91 O    403   80.60   A    8.40
25MCMt13  Rigved          55 C   60 B   80 A   65 B+  67 B+   327   65.40   B+   6.60
25MCMT42  Raja            93 O   90 O   98 O   87 A+  99 O    467   93.40   O    9.80
Class Average Percentage : 79.80
Highest Percentage       : 93.40
Lowest Percentage        : 65.40

Number of students in each grade category:
O  : 1
A+ : 0
A  : 1
B+ : 1
B  : 0
C  : 0
D  : 0
F  : 0
```

---

##  Compilation Instructions

Open terminal inside the **GIT-EXC** folder and run:

```bash
gcc -IHeader Function/*.c -o sprs
```

This compiles all modules together and generates `sprs.exe`.

---

## ▶ Running the Program

```bash
./sprs
```

After execution, the result will be generated in:

```
data/result.txt
```

---

## Features Implemented

### Input & Validation

* Student ID must be alphanumeric
* Student name must contain only alphabets and spaces
* Minor marks range: 0–40
* Major marks range: 0–60

### Computation

* Subject Total = Minor + Major
* Passing marks per subject = 50
* Percentage calculation
* Grade assignment based on percentage
* CGPA calculation using grade points

### Grades and Grade Points

| Grade | Point |
| ----- | ----- |
| O     | 10    |
| A+    | 9     |
| A     | 8     |
| B+    | 7     |
| B     | 6     |
| C     | 5     |
| D     | 4     |
| F     | 0     |

---

##  Modular Design

Modules used in the project:

* `students.h` → Student structure definition
* `validation.c / .h` → ID, name, marks validation
* `grades.c / .h` → Grade and grade-point logic
* `file.c / files.h` → File input and output
* `results.c / results.h` → Result processing and class statistics
* `main.c` → Driver module controlling program flow



##  Testing & Documentation

* Module specifications available in: `Module Specification Document.pdf`
* Test cases and reports available in: `Test-plan.xlsx`

---

##  Notes

* Ensure `students.txt` is present before running the program.
* Do not change the input file format.
* Recompile after every code modification.

---




