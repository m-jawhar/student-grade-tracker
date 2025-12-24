#include "../include/operations.h"

#include <stdio.h>
#include <string.h>

#include "../include/fileio.h"
#include "../include/grading.h"
#include "../include/student.h"

void createProfile() {
  printf("Enter your roll number: ");
  scanf("%d", &myProfile.roll_no);

  getchar();
  printf("Enter your name: ");
  fgets(myProfile.name, sizeof(myProfile.name), stdin);
  myProfile.name[strcspn(myProfile.name, "\n")] = '\0';

  myProfile.currentSemester = 0;
  myProfile.cgpa = 0.0;

  // Initialize all semesters
  for (int i = 0; i < MAX_SEMESTERS; i++) {
    myProfile.semesters[i].subjectCount = 0;
    myProfile.semesters[i].sgpa = 0.0;
  }

  isInitialized = 1;
  printf("\nProfile created successfully!\n");
  printf("Welcome, %s (Roll: %d)!\n", myProfile.name, myProfile.roll_no);
}

void updateProfile() {
  printf("\n=== Update Profile ===\n");
  printf("Current Name: %s\n", myProfile.name);
  printf("Current Roll Number: %d\n\n", myProfile.roll_no);

  printf("Enter new name (or press Enter to keep current): ");
  getchar();
  char newName[50];
  fgets(newName, sizeof(newName), stdin);
  newName[strcspn(newName, "\n")] = '\0';

  if (strlen(newName) > 0) {
    strcpy(myProfile.name, newName);
    printf("Name updated to: %s\n", myProfile.name);
  }

  printf("Enter new roll number (or 0 to keep current): ");
  int newRoll;
  scanf("%d", &newRoll);

  if (newRoll > 0) {
    myProfile.roll_no = newRoll;
    printf("Roll number updated to: %d\n", myProfile.roll_no);
  }

  printf("\nProfile updated successfully!\n");
}

void addSemesterData() {
  printf("\n=== Add/Update Semester Grades ===\n");

  int semNo;
  printf("Enter semester number (1-8): ");
  scanf("%d", &semNo);

  if (semNo < 1 || semNo > MAX_SEMESTERS) {
    printf("Invalid semester number! Must be between 1 and 8.\n");
    return;
  }

  Semester* sem = &myProfile.semesters[semNo - 1];

  // Check if semester already has data
  if (sem->subjectCount > 0) {
    char choice;
    printf("Semester %d already has data. Overwrite? (y/n): ", semNo);
    scanf(" %c", &choice);
    if (choice != 'y' && choice != 'Y') {
      printf("Operation cancelled.\n");
      return;
    }
  }

  printf("Enter number of subjects for semester %d: ", semNo);
  scanf("%d", &sem->subjectCount);

  if (sem->subjectCount > MAX_SUBJECTS_PER_SEMESTER)
    sem->subjectCount = MAX_SUBJECTS_PER_SEMESTER;
  if (sem->subjectCount < 0) sem->subjectCount = 0;

  for (int i = 0; i < sem->subjectCount; i++) {
    getchar();
    printf("\nSubject %d:\n", i + 1);
    printf("  Name: ");
    fgets(sem->subjects[i], sizeof(sem->subjects[i]), stdin);
    sem->subjects[i][strcspn(sem->subjects[i], "\n")] = '\0';

    printf("  Marks (0-100): ");
    scanf("%f", &sem->marks[i]);

    printf("  Credits: ");
    scanf("%d", &sem->credits[i]);
  }

  // Calculate SGPA for this semester
  sem->sgpa = calculateSGPA(sem);
  printf("\n✓ Semester %d SGPA = %.2f\n", semNo, sem->sgpa);

  // Update current semester if this is newer
  if (semNo > myProfile.currentSemester) {
    myProfile.currentSemester = semNo;
  }

  // Recalculate CGPA
  myProfile.cgpa = calculateCGPA(&myProfile);
  printf("✓ Overall CGPA = %.2f\n", myProfile.cgpa);

  printf("\nSemester data saved successfully!\n");
}

void viewSemesterDetails() {
  printf("\n=== View Semester Details ===\n");

  int semNo;
  printf("Enter semester number (1-8): ");
  scanf("%d", &semNo);

  if (semNo < 1 || semNo > MAX_SEMESTERS) {
    printf("Invalid semester number!\n");
    return;
  }

  Semester* sem = &myProfile.semesters[semNo - 1];

  if (sem->subjectCount == 0) {
    printf("No data available for semester %d.\n", semNo);
    return;
  }

  printf("\n=== Semester %d Details ===\n", semNo);
  printf("%-30s %10s %10s %12s\n", "Subject", "Marks", "Credits",
         "Grade Point");
  printf("---------------------------------------------------------------\n");

  for (int i = 0; i < sem->subjectCount; i++) {
    float gradePoint = getGradePoint(sem->marks[i]);
    printf("%-30s %10.2f %10d %12.2f\n", sem->subjects[i], sem->marks[i],
           sem->credits[i], gradePoint);
  }

  printf("---------------------------------------------------------------\n");
  printf("Semester %d SGPA: %.2f\n", semNo, sem->sgpa);
}

// Legacy functions - kept for compatibility
void addStudent() { addSemesterData(); }

void updateStudent() {
  printf("Please use option 1 to add or update semester grades.\n");
}

void deleteStudent() {
  printf("This function is not available in personal grade tracker.\n");
}
