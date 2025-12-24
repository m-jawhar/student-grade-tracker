#include <stdio.h>
#include <stdlib.h>

#include "../include/display.h"
#include "../include/fileio.h"
#include "../include/operations.h"
#include "../include/statistics.h"
#include "../include/student.h"

// Global variables definition
Student myProfile;
int isInitialized = 0;

void showMenu() {
  printf("\n=== My Grade Tracker ===\n");
  printf("1. Add/Update Semester Grades\n");
  printf("2. View My Academic Report\n");
  printf("3. View Semester Details\n");
  printf("4. Show My Progress & Statistics\n");
  printf("5. Update My Profile\n");
  printf("6. Exit\n");
  printf("Enter choice: ");
}

int main() {
  loadFromFile();

  // If first time, create profile
  if (!isInitialized) {
    printf("\n=== Welcome to My Grade Tracker ===\n");
    printf("Let's set up your profile first.\n\n");
    createProfile();
    saveToFile();
  } else {
    printf("\n=== Welcome back, %s! ===\n", myProfile.name);
    printf("Roll Number: %d | Current Semester: %d | CGPA: %.2f\n",
           myProfile.roll_no, myProfile.currentSemester, myProfile.cgpa);
  }

  int choice;
  do {
    showMenu();
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        addSemesterData();
        saveToFile();
        break;
      case 2:
        displayMyReport();
        break;
      case 3:
        viewSemesterDetails();
        break;
      case 4:
        showMyStatistics();
        break;
      case 5:
        updateProfile();
        saveToFile();
        break;
      case 6:
        printf("\nGoodbye, %s! Keep up the great work!\n", myProfile.name);
        break;
      default:
        printf("Invalid choice.\n");
    }
  } while (choice != 6);

  return 0;
}
