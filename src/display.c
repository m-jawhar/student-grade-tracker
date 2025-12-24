#include "../include/display.h"

#include <stdio.h>

#include "../include/grading.h"
#include "../include/student.h"

void printBarGraph(Student s) {
  printf("\n=== My Performance Graph ===\n");
  printf("Name: %s (Roll %d)\n", s.name, s.roll_no);
  printf("Current Semester: %d | CGPA: %.2f\n\n", s.currentSemester, s.cgpa);

  for (int sem = 0; sem < s.currentSemester && sem < MAX_SEMESTERS; sem++) {
    if (s.semesters[sem].subjectCount == 0) continue;

    printf("--- Semester %d (SGPA: %.2f) ---\n", sem + 1,
           s.semesters[sem].sgpa);
    for (int i = 0; i < s.semesters[sem].subjectCount; i++) {
      int bars = (int)(s.semesters[sem].marks[i] / 10);  // 1 '#' per 10 marks
      printf("  %-15s:", s.semesters[sem].subjects[i]);
      for (int j = 0; j < bars; j++) printf("#");
      printf(" (%.1f)\n", s.semesters[sem].marks[i]);
    }
    printf("\n");
  }

  printf("Overall CGPA : ");
  int gpaBars = (int)(s.cgpa);  // 1 '#' per GPA point
  for (int j = 0; j < gpaBars; j++) printf("#");
  printf(" (%.2f)\n", s.cgpa);
}

void displayMyReport() {
  if (!isInitialized || myProfile.currentSemester == 0) {
    printf(
        "\nNo academic data available yet. Please add semester data first.\n");
    return;
  }

  printf("\n========== My Academic Report ==========\n");
  printf("Name: %s\n", myProfile.name);
  printf("Roll Number: %d\n", myProfile.roll_no);
  printf("Current Semester: %d\n", myProfile.currentSemester);
  printf("Cumulative GPA (CGPA): %.2f\n\n", myProfile.cgpa);

  for (int sem = 0; sem < myProfile.currentSemester && sem < MAX_SEMESTERS;
       sem++) {
    if (myProfile.semesters[sem].subjectCount == 0) continue;

    printf("--- Semester %d (SGPA: %.2f) ---\n", sem + 1,
           myProfile.semesters[sem].sgpa);
    printf("%-30s %-10s %-10s %-10s\n", "Subject", "Marks", "Credits",
           "Grade Point");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < myProfile.semesters[sem].subjectCount; i++) {
      float gp = getGradePoint(myProfile.semesters[sem].marks[i]);
      printf("%-30s %-10.1f %-10d %-10.1f\n",
             myProfile.semesters[sem].subjects[i],
             myProfile.semesters[sem].marks[i],
             myProfile.semesters[sem].credits[i], gp);
    }
    printf("\n");
  }

  printBarGraph(myProfile);
}

// Legacy functions kept for compatibility
void displayStudentReport(Student s) { printBarGraph(s); }

void displayStudents() {
  if (!isInitialized) {
    printf("No profile created yet.\n");
    return;
  }

  printf("\n=== My Profile ===\n");
  printf("Name: %s\n", myProfile.name);
  printf("Roll Number: %d\n", myProfile.roll_no);
  printf("Current Semester: %d\n", myProfile.currentSemester);
  printf("CGPA: %.2f\n", myProfile.cgpa);
}

void showRankList() {
  printf("Leaderboard is not available in personal grade tracker.\n");
  printf("This is your personal academic tracking system.\n");
}
