#include "provided.h"
#include "rand_story.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *storyFileName = NULL;
  char *wordsFileName = NULL;

  if (argc == 3) {
    storyFileName = argv[1];
    wordsFileName = argv[2];
  } else if (argc > 3) {
    printf("Too many arguments supplied.\n");
    exit(EXIT_FAILURE);
  } else {
    printf("Two arguments expected.\n");
    exit(EXIT_FAILURE);
  }

  catarray_t catArray = getCategories(wordsFileName);

  for (int i = 0; i < catArray.n; i++) {
    printf("%d ... %s\n", i, catArray.arr[i].name);
    for (int j = 0; j < catArray.arr[i].n_words; j++)
      printf("  %d .. %s\n", j, catArray.arr[i].words[j]);
  }

  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(storyFileName, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  while ((read = getline(&line, &len, fp)) != -1) {

    char *token = strtok(line, " ");
    char *word;

    // loop through the string to extract all other tokens
    while (token != NULL) {

      char *position_ptr_first = strchr(token, '_');
      char *position_ptr_last = strrchr(token, '_');

      int position_first =
          (position_ptr_first == NULL ? -1 : position_ptr_first - token);
      int position_last =
          (position_ptr_last == NULL ? -1 : position_ptr_last - token);

      int count = 0;

      if (position_first != -1 && (position_first == position_last)) {
        // This is ERROR, exit program gracefully
        printf("The input story have incorrect word %s \n", token);
        printf("Exiting program \n");
        exit(0);
      } else if (position_first != position_last) {
        // Call chooseWords functions
        char *oldW = malloc(position_last - position_first);

        strncpy(oldW, token + position_first,
                position_last - position_first + 1);

        char *newW = chooseWord(oldW, NULL);

        // printf("%s %s \n", token, replaceWord(token, oldW, newW));
        word = replaceWord(token, oldW, newW);

      } else {
        // word = malloc(strlen(token));
        word = token;
      }

      // printf("%s | %d %d \n", token, position_first, position_last);
      // printf("%s \n", word);

      token = strtok(NULL, " ");

      printf("%s", word);
      if (token != NULL) {
        printf(" ");
      }
    }
  }

  fclose(fp);
  if (line)
    free(line);
  exit(EXIT_SUCCESS);
}