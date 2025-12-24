#include "../include/statistics.h"

#include <stdio.h>

#include "../include/display.h"
#include "../include/student.h"

void showStatistics() {
  if (studentCount == 0) {
    printf("No data.\n");
    return;
  }
  float total = 0;
  float maxGPA = -1;
  int topperIndex = 0;
  for (int i = 0; i < studentCount; i++) {
    total += students[i].sgpa;
    if (students[i].sgpa > maxGPA) {
      maxGPA = students[i].sgpa;
      topperIndex = i;
    }
  }
  printf("Class Average SGPA: %.2f\n", total / studentCount);
  printf("Topper: %s (Roll %d) SGPA: %.2f\n", students[topperIndex].name,
         students[topperIndex].roll_no, students[topperIndex].sgpa);

  printf("Enter roll number to show bar graph: ");
  int roll;
  scanf("%d", &roll);
  for (int i = 0; i < studentCount; i++) {
    if (students[i].roll_no == roll) {
      printBarGraph(students[i]);
    }
  }
}
