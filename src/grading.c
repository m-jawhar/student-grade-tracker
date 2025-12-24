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

float calculateSGPA(Student* s) {
  int totalCredits = 0;
  float weightedSum = 0.0;

  for (int i = 0; i < s->subjectCount; i++) {
    float gradePoint = getGradePoint(s->marks[i]);
    weightedSum += s->credits[i] * gradePoint;
    totalCredits += s->credits[i];
  }

  if (totalCredits == 0) return 0.0;
  return weightedSum / totalCredits;
}

float calculateCGPA(Student arr[], int n) {
  float totalWeighted = 0.0;
  int totalCredits = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < arr[i].subjectCount; j++) {
      float gp = getGradePoint(arr[i].marks[j]);
      totalWeighted += arr[i].credits[j] * gp;
      totalCredits += arr[i].credits[j];
    }
  }
  if (totalCredits == 0) return 0.0;
  return totalWeighted / totalCredits;
}
