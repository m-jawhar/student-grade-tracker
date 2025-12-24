#include "../include/operations.h"

#include <stdio.h>
#include <string.h>

#include "../include/fileio.h"
#include "../include/grading.h"
#include "../include/student.h"

void addStudent() {
  if (studentCount >= MAX_STUDENTS) {
    printf("Cannot add more students. Limit reached.\n");
    return;
  }
  Student s;
  printf("Enter roll number: ");
  scanf("%d", &s.roll_no);
  getchar();
  printf("Enter name: ");
  fgets(s.name, sizeof(s.name), stdin);
  s.name[strcspn(s.name, "\n")] = '\0';

  printf("Enter number of subjects: ");
  scanf("%d", &s.subjectCount);

  if (s.subjectCount > SUBJECTS) s.subjectCount = SUBJECTS;
  if (s.subjectCount < 0) s.subjectCount = 0;

  for (int i = 0; i < s.subjectCount; i++) {
    getchar();
    printf("Enter subject %d name: ", i + 1);
    fgets(s.subjects[i], sizeof(s.subjects[i]), stdin);
    s.subjects[i][strcspn(s.subjects[i], "\n")] = '\0';

    printf("Enter marks for %s: ", s.subjects[i]);
    scanf("%f", &s.marks[i]);

    printf("Enter credits for %s: ", s.subjects[i]);
    scanf("%d", &s.credits[i]);
  }

  s.sgpa = calculateSGPA(&s);
  students[studentCount++] = s;
  printf("Student added! SGPA = %.2f\n", s.sgpa);
}

void updateStudent() {
  int roll;
  printf("Enter roll number to update: ");
  scanf("%d", &roll);
  for (int i = 0; i < studentCount; i++) {
    if (students[i].roll_no == roll) {
      printf("Updating student %s\n", students[i].name);
      for (int j = 0; j < students[i].subjectCount; j++) {
        printf("Enter new marks for Subject %d: ", j + 1);
        scanf("%f", &students[i].marks[j]);
      }
      students[i].sgpa = calculateSGPA(&students[i]);
      printf("Updated SGPA: %.2f\n", students[i].sgpa);
      saveToFile();
      return;
    }
  }
  printf("Student not found.\n");
}

void deleteStudent() {
  int roll;
  printf("Enter roll number to delete: ");
  scanf("%d", &roll);
  for (int i = 0; i < studentCount; i++) {
    if (students[i].roll_no == roll) {
      for (int j = i; j < studentCount - 1; j++) students[j] = students[j + 1];
      studentCount--;
      printf("Student deleted.\n");
      saveToFile();
      return;
    }
  }
  printf("Student not found.\n");
}
