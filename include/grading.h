#ifndef GRADING_H
#define GRADING_H

#include "student.h"

/**
 * Calculate grade point based on marks (Mar Athanasius College grading system)
 * @param marks Marks obtained (0-100)
 * @return Grade point (0.0 - 10.0)
 */
float getGradePoint(float marks);

/**
 * Calculate SGPA for a student
 * @param s Pointer to Student structure
 * @return SGPA value
 */
float calculateSGPA(Student* s);

/**
 * Calculate CGPA for multiple students
 * @param arr Array of Student structures
 * @param n Number of students
 * @return CGPA value
 */
float calculateCGPA(Student arr[], int n);

#endif  // GRADING_H
