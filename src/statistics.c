#include "../include/statistics.h"

#include <stdio.h>

#include "../include/display.h"
#include "../include/student.h"

void showMyStatistics() {
  if (!isInitialized || myProfile.currentSemester == 0) {
    printf("\nNo academic data available yet.\n");
    return;
  }

  printf("\n=== My Academic Progress & Statistics ===\n");
  printf("Name: %s (Roll %d)\n", myProfile.name, myProfile.roll_no);
  printf("Current Semester: %d\n", myProfile.currentSemester);
  printf("Overall CGPA: %.2f\n\n", myProfile.cgpa);

  // Semester-wise SGPA trend
  printf("Semester-wise Performance:\n");
  printf("%-10s | %-10s | %-15s\n", "Semester", "SGPA", "Trend");
  printf("----------------------------------------\n");

  float prevSGPA = 0.0;
  for (int sem = 0; sem < myProfile.currentSemester && sem < MAX_SEMESTERS;
       sem++) {
    if (myProfile.semesters[sem].subjectCount == 0) continue;

    char trend[20] = "";
    if (sem > 0 && prevSGPA > 0) {
      if (myProfile.semesters[sem].sgpa > prevSGPA + 0.1) {
        strcpy(trend, "↑ Improving");
      } else if (myProfile.semesters[sem].sgpa < prevSGPA - 0.1) {
        strcpy(trend, "↓ Declining");
      } else {
        strcpy(trend, "→ Stable");
      }
    } else {
      strcpy(trend, "—");
    }

    printf("%-10d | %-10.2f | %-15s\n", sem + 1, myProfile.semesters[sem].sgpa,
           trend);
    prevSGPA = myProfile.semesters[sem].sgpa;
  }

  // Best and worst semester
  float bestSGPA = 0.0, worstSGPA = 10.0;
  int bestSem = 0, worstSem = 0;

  for (int sem = 0; sem < myProfile.currentSemester && sem < MAX_SEMESTERS;
       sem++) {
    if (myProfile.semesters[sem].subjectCount == 0) continue;

    if (myProfile.semesters[sem].sgpa > bestSGPA) {
      bestSGPA = myProfile.semesters[sem].sgpa;
      bestSem = sem + 1;
    }
    if (myProfile.semesters[sem].sgpa < worstSGPA) {
      worstSGPA = myProfile.semesters[sem].sgpa;
      worstSem = sem + 1;
    }
  }

  printf("\n");
  if (myProfile.currentSemester > 0) {
    printf("Best Semester: Semester %d (SGPA: %.2f)\n", bestSem, bestSGPA);
    if (myProfile.currentSemester > 1) {
      printf("Weakest Semester: Semester %d (SGPA: %.2f)\n", worstSem,
             worstSGPA);
    }
  }

  // Performance category
  printf("\nPerformance Category: ");
  if (myProfile.cgpa >= 9.0) {
    printf("Outstanding (Distinction)\n");
  } else if (myProfile.cgpa >= 8.0) {
    printf("Excellent (First Class)\n");
  } else if (myProfile.cgpa >= 7.0) {
    printf("Good (Second Class)\n");
  } else if (myProfile.cgpa >= 6.0) {
    printf("Above Average\n");
  } else if (myProfile.cgpa >= 5.5) {
    printf("Average (Pass)\n");
  } else {
    printf("Needs Improvement\n");
  }

  printBarGraph(myProfile);
}

// Legacy function kept for compatibility
void showStatistics() { showMyStatistics(); }
