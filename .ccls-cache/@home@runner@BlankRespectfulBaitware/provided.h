#ifndef __PROVIDED_H__
#define __PROVIDED_H__

#include "helper.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct category_tag {
  char *name;
  char **words;
  size_t n_words;
};

typedef struct category_tag category_t;

struct catarray_tag {
  category_t *arr;
  size_t n;
};

typedef struct catarray_tag catarray_t;

const char *chooseWord(char *category, catarray_t *cats) {
  char *word = strdup(category);

  // printf("%s - ", category);
  removeChar(word, word[0]);
  // printf("%s - %s \n", category, word);

  printf("%i \n", cats->n);
  printf("%s \n", cats->arr[0].name);

  for (int i = 0; i < cats->n; i++) {

    // if (strcmp(cats->arr[i].name, word) == 0) {
    //   printf("%s category found \n", word);
    // }
    // for (int j = 0; j < cats.arr[i].n_words; j++)
  }

  return "cat";
}

void printWords(catarray_t *cats);

#endif
