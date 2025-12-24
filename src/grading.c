#include "../include/grading.h"

#include <stdio.h>

float getGradePoint(float marks) {
  if (marks >= 90)
    return 10.0;  // S grade
  else if (marks >= 85)
    return 9.0;  // A+ grade
  else if (marks >= 80)
    return 8.5;  // A grade
  else if (marks >= 75)
    return 8.0;  // B+ grade
  else if (marks >= 70)
    return 7.5;  // B grade
  else if (marks >= 65)
    return 7.0;  // C+ grade
  else if (marks >= 60)
    return 6.5;  // C grade
  else if (marks >= 55)
    return 6.0;  // D grade
  else if (marks >= 50)
    return 5.5;  // P (Pass) grade
  else
    return 0.0;  // F (Fail) - < 50% overall
}

float calculateSGPA(Semester* semester) {
  int totalCredits = 0;
  float weightedSum = 0.0;

  for (int i = 0; i < semester->subjectCount; i++) {
    float gradePoint = getGradePoint(semester->marks[i]);
    weightedSum += semester->credits[i] * gradePoint;
    totalCredits += semester->credits[i];
  }

  if (totalCredits == 0) return 0.0;
  return weightedSum / totalCredits;
}

float calculateCGPA(Student* student) {
  float totalWeighted = 0.0;
  int totalCredits = 0;

  // Sum across all completed semesters (1 to currentSemester)
  for (int sem = 0; sem < student->currentSemester && sem < MAX_SEMESTERS;
       sem++) {
    Semester* s = &student->semesters[sem];
    for (int j = 0; j < s->subjectCount; j++) {
      float gp = getGradePoint(s->marks[j]);
      totalWeighted += s->credits[j] * gp;
      totalCredits += s->credits[j];
    }
  }

  if (totalCredits == 0) return 0.0;
  return totalWeighted / totalCredits;
}
