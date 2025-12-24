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
 * Calculate SGPA for a specific semester
 * @param semester Pointer to Semester structure
 * @return SGPA value for that semester
 */
float calculateSGPA(Semester* semester);

/**
 * Calculate CGPA for a student across all completed semesters
 * @param student Pointer to Student structure
 * @return CGPA value across all semesters
 */
float calculateCGPA(Student* student);

#endif  // GRADING_H
