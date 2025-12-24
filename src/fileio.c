#include "../include/fileio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/grading.h"
#include "../include/student.h"

void saveToFile() {
  FILE* fp = fopen(FILENAME, "w");
  if (!fp) {
    printf("Error opening file for writing.\n");
    return;
  }

  if (!isInitialized) {
    fclose(fp);
    return;
  }

  // Write: roll_no, name, currentSemester, cgpa
  fprintf(fp, "%d,%s,%d,%.2f\n", myProfile.roll_no, myProfile.name,
          myProfile.currentSemester, myProfile.cgpa);

  // Write each semester's data
  for (int sem = 0; sem < myProfile.currentSemester && sem < MAX_SEMESTERS;
       sem++) {
    if (myProfile.semesters[sem].subjectCount == 0) continue;

    Semester* s = &myProfile.semesters[sem];

    // Semester line: semester_number, subjectCount, sgpa
    fprintf(fp, "SEM,%d,%d,%.2f\n", sem + 1, s->subjectCount, s->sgpa);

    // Write each subject: subject_name, marks, credits
    for (int j = 0; j < s->subjectCount; j++) {
      fprintf(fp, "SUBJ,%s,%.2f,%d\n", s->subjects[j], s->marks[j],
              s->credits[j]);
    }
  }

  // End marker
  fprintf(fp, "END\n");

  fclose(fp);
}

void loadFromFile() {
  FILE* fp = fopen(FILENAME, "r");
  if (!fp) {
    isInitialized = 0;
    return;  // No file, first time user
  }

  char line[256];

  // Parse profile line: roll_no, name, currentSemester, cgpa
  if (fgets(line, sizeof(line), fp)) {
    if (sscanf(line, "%d,%49[^,],%d,%f", &myProfile.roll_no, myProfile.name,
               &myProfile.currentSemester, &myProfile.cgpa) == 4) {
      isInitialized = 1;
    } else {
      fclose(fp);
      isInitialized = 0;
      return;
    }
  } else {
    fclose(fp);
    isInitialized = 0;
    return;
  }

  // Initialize all semesters
  for (int i = 0; i < MAX_SEMESTERS; i++) {
    myProfile.semesters[i].subjectCount = 0;
    myProfile.semesters[i].sgpa = 0.0;
  }

  // Read semester data
  while (fgets(line, sizeof(line), fp)) {
    if (strncmp(line, "END", 3) == 0) {
      break;  // End of data
    }

    if (strncmp(line, "SEM,", 4) == 0) {
      int semNum, subCount;
      float sgpa;
      if (sscanf(line, "SEM,%d,%d,%f", &semNum, &subCount, &sgpa) == 3) {
        if (semNum >= 1 && semNum <= MAX_SEMESTERS) {
          Semester* sem = &myProfile.semesters[semNum - 1];
          sem->subjectCount = subCount;
          sem->sgpa = sgpa;

          // Read subjects for this semester
          for (int j = 0; j < subCount; j++) {
            if (fgets(line, sizeof(line), fp)) {
              if (strncmp(line, "SUBJ,", 5) == 0) {
                sscanf(line, "SUBJ,%49[^,],%f,%d", sem->subjects[j],
                       &sem->marks[j], &sem->credits[j]);
              }
            }
          }
        }
      }
    }
  }

  // Recalculate SGPA and CGPA to ensure consistency
  for (int sem = 0; sem < myProfile.currentSemester && sem < MAX_SEMESTERS;
       sem++) {
    if (myProfile.semesters[sem].subjectCount > 0) {
      myProfile.semesters[sem].sgpa = calculateSGPA(&myProfile.semesters[sem]);
    }
  }
  myProfile.cgpa = calculateCGPA(&myProfile);

  fclose(fp);
}
