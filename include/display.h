#ifndef DISPLAY_H
#define DISPLAY_H

#include "student.h"

/**
 * Display performance bar graph for a student
 * @param s Student structure
 */
void printBarGraph(Student s);

/**
 * Display detailed report for a student
 * @param s Student structure
 */
void displayStudentReport(Student s);

/**
 * Display all students in tabular format
 */
void displayStudents();

/**
 * Display students ranked by SGPA
 */
void showRankList();

#endif  // DISPLAY_H
