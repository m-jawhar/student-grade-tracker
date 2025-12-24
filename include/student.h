#ifndef STUDENT_H
#define STUDENT_H

#define MAX_SUBJECTS_PER_SEMESTER 10
#define MAX_SEMESTERS 8  // 4 years * 2 semesters
#define FILENAME "data/my_grades.csv"

// Represents one semester's data
typedef struct {
  int subjectCount;  // Number of subjects in this semester
  char subjects[MAX_SUBJECTS_PER_SEMESTER][50];  // Subject names
  float marks[MAX_SUBJECTS_PER_SEMESTER];        // Marks out of 100
  int credits[MAX_SUBJECTS_PER_SEMESTER];        // Credits per subject
  float sgpa;                                    // Semester GPA
} Semester;

// Represents a student with multiple semesters
typedef struct {
  int roll_no;
  char name[50];
  int currentSemester;  // Current semester (1-8), 0 if not enrolled
  Semester semesters[MAX_SEMESTERS];  // Data for up to 8 semesters
  float cgpa;  // Cumulative GPA across all completed semesters
} Student;

extern Student myProfile;  // Single student profile
extern int isInitialized;  // Whether profile has been created

#endif  // STUDENT_H
