#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define SUBJECTS 10
#define FILENAME "students.csv"

typedef struct {
  int roll_no;
  char name[50];
  int subjectCount;
  char subjects[10][50];  // Max 10 subjects
  float marks[10];        // Marks out of 100
  int credits[10];        // Credits assigned to each subject
  float sgpa;             // Semester GPA
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

/* ---------- Utility Functions ---------- */
int getGradePoint(float marks) {
  if (marks >= 90)
    return 10;
  else if (marks >= 80)
    return 9;
  else if (marks >= 70)
    return 8;
  else if (marks >= 60)
    return 7;
  else if (marks >= 50)
    return 6;
  else if (marks >= 40)
    return 5;
  else
    return 0;  // Fail
}

float calculateSGPA(Student* s) {
  int totalCredits = 0;
  float weightedSum = 0.0;

  for (int i = 0; i < s->subjectCount; i++) {
    int gradePoint = getGradePoint(s->marks[i]);
    weightedSum += s->credits[i] * gradePoint;
    totalCredits += s->credits[i];
  }

  if (totalCredits == 0) return 0.0;
  return weightedSum / totalCredits;
}

float calculateCGPA(Student arr[], int n) {
  float totalWeighted = 0.0;
  int totalCredits = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < arr[i].subjectCount; j++) {
      int gp = getGradePoint(arr[i].marks[j]);
      totalWeighted += arr[i].credits[j] * gp;
      totalCredits += arr[i].credits[j];
    }
  }
  if (totalCredits == 0) return 0.0;
  return totalWeighted / totalCredits;
}

void saveToFile() {
  FILE* fp = fopen(FILENAME, "w");
  if (!fp) {
    printf("Error opening file for writing.\n");
    return;
  }

  for (int i = 0; i < studentCount; i++) {
    Student* s = &students[i];
    // roll_no, name, subjectCount
    fprintf(fp, "%d,%s,%d", s->roll_no, s->name, s->subjectCount);

    // each subject: name, marks, credits
    for (int j = 0; j < s->subjectCount; j++) {
      fprintf(fp, ",%s,%.2f,%d", s->subjects[j], s->marks[j], s->credits[j]);
    }

    // SGPA at the end
    fprintf(fp, ",%.2f\n", s->sgpa);
  }

  fclose(fp);
}

void loadFromFile() {
  FILE* fp = fopen(FILENAME, "r");
  if (!fp) return;  // No file yet
  studentCount = 0;

  while (!feof(fp)) {
    Student s;
    if (fscanf(fp, "%d,%49[^,],%d", &s.roll_no, s.name, &s.subjectCount) != 3)
      break;

    for (int j = 0; j < s.subjectCount; j++) {
      if (fscanf(fp, ",%49[^,],%f,%d", s.subjects[j], &s.marks[j],
                 &s.credits[j]) != 3)
        break;
    }

    fscanf(fp, ",%f\n", &s.sgpa);

    // Recalculate SGPA to ensure consistency
    s.sgpa = calculateSGPA(&s);

    students[studentCount++] = s;
  }

  fclose(fp);
}

/* ---------- Core Features ---------- */
void addStudent() {
  Student s;
  printf("Enter roll number: ");
  scanf("%d", &s.roll_no);
  getchar();
  printf("Enter name: ");
  fgets(s.name, sizeof(s.name), stdin);
  s.name[strcspn(s.name, "\n")] = '\0';

  printf("Enter number of subjects: ");
  scanf("%d", &s.subjectCount);

  for (int i = 0; i < s.subjectCount; i++) {
    getchar();
    printf("Enter subject %d name: ", i + 1);
    fgets(s.subjects[i], sizeof(s.subjects[i]), stdin);
    s.subjects[i][strcspn(s.subjects[i], "\n")] = '\0';

    printf("Enter marks for %s: ", s.subjects[i]);
    scanf("%f", &s.marks[i]);

    printf("Enter credits for %s: ", s.subjects[i]);
    scanf("%d", &s.credits[i]);
  }

  s.sgpa = calculateSGPA(&s);
  students[studentCount++] = s;
  printf("Student added! SGPA = %.2f\n", s.sgpa);
}

void displayStudentReport(Student s) {
  printf("\nReport for %s (Roll %d):\n", s.name, s.roll_no);
  printf("%-15s %-10s %-10s %-10s\n", "Subject", "Marks", "Credits",
         "Grade Point");
  for (int i = 0; i < s.subjectCount; i++) {
    int gp = getGradePoint(s.marks[i]);
    printf("%-15s %-10.1f %-10d %-10d\n", s.subjects[i], s.marks[i],
           s.credits[i], gp);
  }
  printf("SGPA: %.2f\n", s.sgpa);
}

void displayStudents() {
  if (studentCount == 0) {
    printf("No students available.\n");
    return;
  }

  printf("\n%-5s %-20s ", "Roll", "Name");

  // Use the first student's subject names for header
  for (int j = 0; j < students[0].subjectCount; j++)
    printf("%-10s ", students[0].subjects[j]);

  printf("SGPA\n");
  printf(
      "------------------------------------------------------------------------"
      "-------\n");

  for (int i = 0; i < studentCount; i++) {
    printf("%-5d %-20s ", students[i].roll_no, students[i].name);
    for (int j = 0; j < students[i].subjectCount; j++)
      printf("%-10.1f ", students[i].marks[j]);
    printf("%-5.2f\n", students[i].sgpa);
  }
}

void updateStudent() {
  int roll;
  printf("Enter roll number to update: ");
  scanf("%d", &roll);
  for (int i = 0; i < studentCount; i++) {
    if (students[i].roll_no == roll) {
      printf("Updating student %s\n", students[i].name);
      for (int j = 0; j < students[i].subjectCount; j++) {
        printf("Enter new marks for Subject %d: ", j + 1);
        scanf("%f", &students[i].marks[j]);
      }
      students[i].sgpa = calculateSGPA(&students[i]);
      printf("Updated SGPA: %.2f\n", students[i].sgpa);
      saveToFile();
      return;
    }
  }
  printf("Student not found.\n");
}

void deleteStudent() {
  int roll;
  printf("Enter roll number to delete: ");
  scanf("%d", &roll);
  for (int i = 0; i < studentCount; i++) {
    if (students[i].roll_no == roll) {
      for (int j = i; j < studentCount - 1; j++) students[j] = students[j + 1];
      studentCount--;
      printf("Student deleted.\n");
      saveToFile();
      return;
    }
  }
  printf("Student not found.\n");
}

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
}

/* ---------- Menu ---------- */
void showMenu() {
  printf("\n=== Smart Academic Performance Dashboard ===\n");
  printf("1. Add Student\n");
  printf("2. Display Students\n");
  printf("3. Update Student\n");
  printf("4. Delete Student\n");
  printf("5. Show Statistics\n");
  printf("6. Exit\n");
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
        saveToFile();
        printf("Goodbye!\n");
        exit(0);
      default:
        printf("Invalid choice.\n");
    }
  }
  return 0;
}
