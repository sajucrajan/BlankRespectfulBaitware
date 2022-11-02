#ifndef __PROVIDED_H__
#define __PROVIDED_H__

#include "helper.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

  char* randomWord;

  // printf("%i \n", cats->n);
  // printf("%s \n", cats->arr[0].name);

  for (int i = 0; i < cats->n; i++) {

    if (strcmp(cats->arr[i].name, word) == 0) {
      srand(time(0));
      int randomNumber = (rand() % (cats->arr[i].n_words));
      
      // printf("%i - %s category found \n", randomNumber, word);
      randomWord = strdup(cats->arr[i].words[randomNumber]);

      // printf("%s \n", randomWord);

    }
  }

  return randomWord;
}

void printWords(catarray_t *cats);

#endif
