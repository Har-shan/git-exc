
#  Student Result Processing System (C)

##  Overview

This task implements a **Student Result Processing System** in **C programming language** using **file handling, structures, and modular programming**.

The system:

* Reads student details from an **input file**
* Validates the data
* Computes **subject-wise totals, grades, overall grade, CGPA**
* Calculates **class-level statistics**
* Writes the complete result to an **output file**


---

##  Files Used

###  `students.txt` (Input File)

Contains student details.

**Format:**

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



###  `result.txt` (Output File)

Generated automatically by the program.

Contains:

* Student-wise subject totals & grades
* Total marks, percentage
* Overall grade
* CGPA
* Class statistics (average, highest, lowest, grade distribution)

---

##  Features Implemented

###  Input & Validation

* Student ID must be **alphanumeric**
* Student name must contain **only alphabets and spaces**
* Minor marks: **0–40**
* Major marks: **0–60**
* Invalid records are detected and reported

---

###  Computation

* Subject Total = Minor + Major
* Minimum passing marks per subject = **50**
* Percentage = Total / 5
* **Subject-wise grades**
* **Overall grade based on percentage**
* **CGPA calculated using grade points**

#### Grade to Grade-Point Mapping:

| Grade | Grade Point |
| ----- | ----------- |
| O     | 10          |
| A+    | 9           |
| A     | 8           |
| B+    | 7           |
| B     | 6           |
| C     | 5           |
| D     | 4           |
| F     | 0           |

CGPA = Average of subject grade points
(If any subject is failed → CGPA = 0)

---

### Output & Statistics

* Tabular student result report
* **Class Average Percentage**
* **Highest Percentage**
* **Lowest Percentage**
* **Number of students in each grade category**

---

##  Programming Concepts Used

* Structures (`struct`)
* File handling (`fopen`, `fscanf`, `fprintf`, `fclose`)
* Modular programming (functions for input, validation, processing, output)
* Arrays
* String handling
* Conditional logic

---

##  How to Compile & Run

### Compile

```bash
gcc sprs1.c -o sprs1
```

### Run

```bash
./sprs1
```



