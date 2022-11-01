#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STUDENT_SIZE 273
typedef struct {
  int stNo, points;
  char name[40];
} Student;

int readTxtFile(const char *filename, Student *students) {
  FILE *fin = fopen(filename, "r");
  if (!fin) {
    printf("Can't open file: %s\n", filename);
    return 0;
  }
  int i = 0;

  /*
  while (fscanf(fin, "%d,%s,%d\n", &students[i].stNo, students[i].name,
                  &students[i].points)) {
      ++i;
    }
  */

  while (!feof(fin)) {
    fscanf(fin, "%d,%s,%d\n", &students[i].stNo, students[i].name,
           &students[i].points);
    i++;
  }

  i = 0;
  char *lineptr = NULL;
  size_t size = 0;
  while (getline(&lineptr, &size, fin) != -1) {
    printf("source line %s \n", lineptr);
    i++;
  }
  fclose(fin);
  return i;
}

/*
int readTxtFile2(const char *filename, Student *students) {
  FILE *fin = fopen(filename, "r");
  if (!fin) {
    printf("Can't open file: %s\n", filename);
    return 0;
  }
  int i = 0;

  char *lineptr = NULL;
  size_t size = 0;
  /*
  ssize_t getline(char **lineptr, size_t *n, FILE *stream);
  while (fscanf(fin, "%d%s %d",
                &students[i].stNo,
                students[i].name,
                &students[i].points))
  --star/

  while (getline(&lineptr, &size, fin) != -1) {
    parse_line_to_struct_members(lineptr, &students[i].stNo, students[i].name,
                                 &students[i].points);
    i++;
  }
  free(lineptr);
  lineptr = NULL;
  fclose(fin);
  return i;
}

void parse_line_to_struct_members(char *line, int *num, char *name,
                                  int *points) {
  char *tok = NULL;

  // stNo
  tok = strtok(line, ",");
  if (tok)
    *num = atoi(tok);
  // name
  tok = strtok(NULL, ",");
  if (tok)
    strcpy(name, tok);

  // points
  tok = strtok(NULL, ",");
  if (tok)
    *points = atoi(tok);
}
*/

void printArray(Student *students, int size) {
  for (int i = 0; i < size; i++) {
    Student *st = &students[i];
    printf("%d,%s,%d\n", st->stNo, st->name, st->points);
  }
}
int main() {
  Student students[STUDENT_SIZE];
  char myFile[] = "person.dat";
  int size = readTxtFile(myFile, students);
  printArray(students, size);
  return 0;
}