#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100
#define SUBJECTS 10
#define FILENAME "data/students.csv"

typedef struct {
  int roll_no;
  char name[50];
  int subjectCount;
  char subjects[10][50];  // Max 10 subjects
  float marks[10];        // Marks out of 100
  int credits[10];        // Credits assigned to each subject
  float sgpa;             // Semester GPA
} Student;

extern Student students[MAX_STUDENTS];
extern int studentCount;

#endif  // STUDENT_H
