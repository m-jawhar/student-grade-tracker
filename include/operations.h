#ifndef OPERATIONS_H
#define OPERATIONS_H

/**
 * Create initial student profile (first time setup)
 */
void createProfile();

/**
 * Update student profile information (name, roll number)
 */
void updateProfile();

/**
 * Add or update semester grades
 */
void addSemesterData();

/**
 * View detailed information for a specific semester
 */
void viewSemesterDetails();

// Legacy functions for compatibility
void addStudent();
void updateStudent();
void deleteStudent();

#endif  // OPERATIONS_H
