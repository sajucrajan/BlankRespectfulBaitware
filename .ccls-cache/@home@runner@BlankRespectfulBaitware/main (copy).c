#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  char *fileName = NULL;

  if (argc == 2) {
    fileName = argv[1];
  } else if (argc > 2) {
    printf("Too many arguments supplied.\n");
  } else {
    printf("One argument expected.\n");
  }

  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(fileName, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  while ((read = getline(&line, &len, fp)) != -1) {
    printf("%s", line);
  }

  fclose(fp);
  if (line)
    free(line);
  exit(EXIT_SUCCESS);
}