#include <stdio.h>
#include <stdlib.h>

#include "../include/display.h"
#include "../include/fileio.h"
#include "../include/operations.h"
#include "../include/statistics.h"
#include "../include/student.h"

// Global variables definition
Student students[MAX_STUDENTS];
int studentCount = 0;

void showMenu() {
  printf("\n=== Smart Academic Performance Dashboard ===\n");
  printf("1. Add Student\n");
  printf("2. Display Students\n");
  printf("3. Update Student\n");
  printf("4. Delete Student\n");
  printf("5. Show Statistics\n");
  printf("6. Show Leaderboard\n");
  printf("7. Exit\n");
  printf("Enter choice: ");
}

int main() {
  loadFromFile();
  int choice;
  while (1) {
    showMenu();
    scanf("%d", &choice);
    switch (choice) {
      case 1:
        addStudent();
        break;
      case 2:
        displayStudents();
        break;
      case 3:
        updateStudent();
        break;
      case 4:
        deleteStudent();
        break;
      case 5:
        showStatistics();
        break;
      case 6:
        showRankList();
        break;
      case 7:
        saveToFile();
        printf("Goodbye!\n");
        exit(0);

      default:
        printf("Invalid choice.\n");
    }
  }
  return 0;
}
