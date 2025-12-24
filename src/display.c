#include "../include/display.h"

#include <stdio.h>

#include "../include/grading.h"
#include "../include/student.h"

void printBarGraph(Student s) {
  printf("\nPerformance Graph for %s (Roll %d):\n", s.name, s.roll_no);
  for (int i = 0; i < s.subjectCount; i++) {
    int bars = (int)(s.marks[i] / 10);  // 1 '#' per 10 marks
    printf("%-8s:", s.subjects[i]);
    for (int j = 0; j < bars; j++) printf("#");
    printf(" (%.1f)\n", s.marks[i]);
  }
  printf("SGPA     : ");
  int gpaBars = (int)(s.sgpa);  // 1 '#' per GPA point
  for (int j = 0; j < gpaBars; j++) printf("#");
  printf(" (%.2f)\n", s.sgpa);
}

void displayStudentReport(Student s) {
  printf("\nReport for %s (Roll %d):\n", s.name, s.roll_no);
  printf("%-15s %-10s %-10s %-10s\n", "Subject", "Marks", "Credits",
         "Grade Point");
  for (int i = 0; i < s.subjectCount; i++) {
    float gp = getGradePoint(s.marks[i]);
    printf("%-15s %-10.1f %-10d %-10.1f\n", s.subjects[i], s.marks[i],
           s.credits[i], gp);
  }
  printf("SGPA: %.2f\n", s.sgpa);
}

void displayStudents() {
  if (studentCount == 0) {
    printf("No students available.\n");
    return;
  }

  printf("\n%-5s %-20s ", "Roll", "Name");

  // Use the first student's subject names for header
  for (int j = 0; j < students[0].subjectCount; j++)
    printf("%-10s ", students[0].subjects[j]);

  printf("SGPA\n");
  printf(
      "------------------------------------------------------------------------"
      "-------\n");

  for (int i = 0; i < studentCount; i++) {
    printf("%-5d %-20s ", students[i].roll_no, students[i].name);
    for (int j = 0; j < students[i].subjectCount; j++)
      printf("%-10.1f ", students[i].marks[j]);
    printf("%-5.2f\n", students[i].sgpa);
  }
}

void showRankList() {
  if (studentCount == 0) {
    printf("No students available.\n");
    return;
  }

  // Create a temporary copy to sort
  Student temp[MAX_STUDENTS];
  for (int i = 0; i < studentCount; i++) {
    temp[i] = students[i];
  }

  // Sort by SGPA (descending)
  for (int i = 0; i < studentCount - 1; i++) {
    for (int j = i + 1; j < studentCount; j++) {
      if (temp[i].sgpa < temp[j].sgpa) {
        Student swap = temp[i];
        temp[i] = temp[j];
        temp[j] = swap;
      }
    }
  }

  printf("\n=== SGPA Rank List ===\n");
  for (int i = 0; i < studentCount; i++) {
    printf("%2d. %-20s (Roll %d) SGPA: %.2f | ", i + 1, temp[i].name,
           temp[i].roll_no, temp[i].sgpa);

    int bars = (int)(temp[i].sgpa);  // 1 bar = 1 SGPA point
    for (int b = 0; b < bars; b++) printf("#");
    printf("\n");
  }
}
