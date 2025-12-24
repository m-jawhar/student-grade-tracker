#ifndef DISPLAY_H
#define DISPLAY_H

#include "student.h"

/**
 * Display my complete academic report with all semesters
 */
void displayMyReport();

/**
 * Display performance bar graph for a student
 * @param s Student structure
 */
void printBarGraph(Student s);

// Legacy functions for compatibility
void displayStudentReport(Student s);
void displayStudents();
void showRankList();

#endif  // DISPLAY_H
