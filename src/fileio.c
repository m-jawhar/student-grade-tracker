#include "../include/fileio.h"

#include <stdio.h>

#include "../include/grading.h"
#include "../include/student.h"

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
  while (!feof(fp) && studentCount < MAX_STUDENTS) {
    Student s;
    if (fscanf(fp, "%d,%49[^,],%d", &s.roll_no, s.name, &s.subjectCount) != 3)
      break;

    if (s.subjectCount > SUBJECTS) s.subjectCount = SUBJECTS;
    if (s.subjectCount < 0) s.subjectCount = 0;

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
