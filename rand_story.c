#include "provided.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replaceWord(const char *s, const char *oldW, const char *newW) {
  char *result;
  int i, cnt = 0;
  int newWlen = strlen(newW);
  int oldWlen = strlen(oldW);

  // Counting the number of times old word
  // occur in the string
  for (i = 0; s[i] != '\0'; i++) {
    if (strstr(&s[i], oldW) == &s[i]) {
      cnt++;

      // Jumping to index after the old word.
      i += oldWlen - 1;
    }
  }

  // Making new string of enough length
  result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);

  i = 0;
  while (*s) {
    // compare the substring with the result
    if (strstr(s, oldW) == s) {
      strcpy(&result[i], newW);
      i += newWlen;
      s += oldWlen;
    } else
      result[i++] = *s++;
  }

  result[i] = '\0';
  return result;
}

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

catarray_t getCategories(char *wordsFileName) {

  FILE *fpi;
  char *linei = NULL;
  size_t len = 0;
  ssize_t read;

  char buf1[20], buf2[20], buffer[255];
  category_t cats[5];

  catarray_t catArray;

  memset(buf1, '\0', 20);
  memset(buf2, '\0', 20);
  memset(buffer, '\0', 255);

  fpi = fopen(wordsFileName, "r");
  if (fpi == NULL)
    exit(EXIT_FAILURE);

  for (int i = 0; i < 5; i++) {
    cats[i].n_words = 0;
  }
  int arr_ctr = 0;

  int cat_cnt = 0;
  while (fgets(buffer, 255, fpi) != NULL) {
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
      cats[cat_cnt].words = (char **)malloc(50 * sizeof(char));
      cats[cat_cnt].words[cats[cat_cnt].n_words] = strdup(buf2);
      cats[cat_cnt].n_words += 1;
      cat_cnt += 1;
    } else {
      cats[bPos].words[cats[bPos].n_words] = strdup(buf2);
      cats[bPos].n_words += 1;
    }
  }

  catArray.arr = &cats[0];
  catArray.n = cat_cnt;

  // // for (int i = 0; i < cat_cnt; i++) {
  // //   printf("%d ... %s\n", i, cats[i].name);
  // //   for (int j = 0; j < cats[i].n_words; j++)
  // //     printf("  %d .. %s\n", j, cats[i].words[j]);
  // // }

  fclose(fpi);
  if (linei)
    free(linei);
  
  return catArray;
}