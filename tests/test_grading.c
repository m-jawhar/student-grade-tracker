#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../include/grading.h"
#include "../include/student.h"

void test_getGradePoint() {
  printf("Testing getGradePoint()...\n");

  // Test S grade
  assert(getGradePoint(95.0) == 10.0);
  assert(getGradePoint(90.0) == 10.0);

  // Test A+ grade
  assert(getGradePoint(87.0) == 9.0);
  assert(getGradePoint(85.0) == 9.0);

  // Test A grade
  assert(getGradePoint(82.0) == 8.5);
  assert(getGradePoint(80.0) == 8.5);

  // Test B+ grade
  assert(getGradePoint(77.0) == 8.0);
  assert(getGradePoint(75.0) == 8.0);

  // Test B grade
  assert(getGradePoint(72.0) == 7.5);
  assert(getGradePoint(70.0) == 7.5);

  // Test P grade
  assert(getGradePoint(52.0) == 5.5);
  assert(getGradePoint(50.0) == 5.5);

  // Test F grade
  assert(getGradePoint(45.0) == 0.0);
  assert(getGradePoint(0.0) == 0.0);

  printf("✓ All getGradePoint tests passed!\n");
}

void test_calculateSGPA() {
  printf("\nTesting calculateSGPA()...\n");

  Student s;
  s.roll_no = 1;
  strcpy(s.name, "Test Student");
  s.subjectCount = 3;

  strcpy(s.subjects[0], "Math");
  s.marks[0] = 90.0;  // Grade: 10.0
  s.credits[0] = 4;

  strcpy(s.subjects[1], "Physics");
  s.marks[1] = 80.0;  // Grade: 8.5
  s.credits[1] = 3;

  strcpy(s.subjects[2], "Chemistry");
  s.marks[2] = 70.0;  // Grade: 7.5
  s.credits[2] = 3;

  // Expected SGPA = (10*4 + 8.5*3 + 7.5*3) / (4+3+3) = 88/10 = 8.8
  float sgpa = calculateSGPA(&s);
  assert(sgpa > 8.79 && sgpa < 8.81);

  printf("✓ calculateSGPA test passed! SGPA = %.2f\n", sgpa);
}

void test_calculateCGPA() {
  printf("\nTesting calculateCGPA()...\n");

  Student students[2];

  // Student 1
  students[0].subjectCount = 2;
  students[0].marks[0] = 90.0;  // Grade: 10.0
  students[0].credits[0] = 4;
  students[0].marks[1] = 80.0;  // Grade: 8.5
  students[0].credits[1] = 4;

  // Student 2
  students[1].subjectCount = 2;
  students[1].marks[0] = 70.0;  // Grade: 7.5
  students[1].credits[0] = 3;
  students[1].marks[1] = 60.0;  // Grade: 6.5
  students[1].credits[1] = 3;

  // Expected CGPA = (10*4 + 8.5*4 + 7.5*3 + 6.5*3) / (4+4+3+3) = 116/14
  // = 8.285...
  float cgpa = calculateCGPA(students, 2);
  assert(cgpa > 8.28 && cgpa < 8.29);

  printf("✓ calculateCGPA test passed! CGPA = %.2f\n", cgpa);
}

void test_edge_cases() {
  printf("\nTesting edge cases...\n");

  Student s;
  s.subjectCount = 0;

  // Test with zero subjects
  float sgpa = calculateSGPA(&s);
  assert(sgpa == 0.0);

  // Test with zero credits
  s.subjectCount = 1;
  s.marks[0] = 90.0;
  s.credits[0] = 0;
  sgpa = calculateSGPA(&s);
  assert(sgpa == 0.0);

  printf("✓ Edge case tests passed!\n");
}

int main(void) {
  printf("=== Running Student Management System Tests ===\n\n");

  test_getGradePoint();
  test_calculateSGPA();
  test_calculateCGPA();
  test_edge_cases();

  printf("\n=== All tests passed! ✓ ===\n");
  return 0;
}
