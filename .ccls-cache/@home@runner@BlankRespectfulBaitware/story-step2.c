#include "provided.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SplitLine(char line[255], char buf1[20], char buf2[20], char delimiter) {

  if (line == NULL) {
    perror("Empty Line!");
    exit(EXIT_FAILURE);
  }
  int i = 0;

  while (i < strlen(line) && line[i] != delimiter) {
    buf1[i] = line[i];
    i++;
  }
  buf1[i] = '\0';
  i++;
  int j = 0;
  while (i < strlen(line) && line[i] != '\n') {
    buf2[j] = line[i];
    i++;
    j++;
  }
  buf2[j] = '\0';
}

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

  char buf1[20], buf2[20], buffer[255];
  struct category_tag cats[5];

  memset(buf1, '\0', 20);
  memset(buf2, '\0', 20);
  memset(buffer, '\0', 255);

  fp = fopen(fileName, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  for (int i = 0; i < 5; i++) {
    cats[i].n_words = 0;
  }
  int arr_ctr = 0;

  int cat_cnt = 0;
  while (fgets(buffer, 255, fp) != NULL) {
    int bFound = 0;
    int bPos = 0;

    SplitLine(buffer, buf1, buf2, ':');

    for (int i = 0; i < cat_cnt; i++) {
      if (strncmp(cats[i].name, buf1, strlen(buf1)) == 0) {
        bFound = 1;
        bPos = i;
        break;
      }
    }
    if (!bFound) {
      cats[cat_cnt].name = strdup(buf1);
      cats[cat_cnt].words = (char **)malloc(10 * sizeof(char));
      cats[cat_cnt].words[cats[cat_cnt].n_words] = strdup(buf2);
      cats[cat_cnt].n_words += 1;
      cat_cnt += 1;
    } else {
      cats[bPos].words[cats[bPos].n_words] = strdup(buf2);
      cats[bPos].n_words += 1;
    }
  }

  for (int i = 0; i < cat_cnt; i++) {
    printf("%d ... %s\n", i, cats[i].name);
    for (int j = 0; j < cats[i].n_words; j++)
      printf("  %d .. %s\n", j, cats[i].words[j]);
  }

  fclose(fp);
  if (line)
    free(line);
  exit(EXIT_SUCCESS);
}