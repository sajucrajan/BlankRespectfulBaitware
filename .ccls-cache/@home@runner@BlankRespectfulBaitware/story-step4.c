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

  printf("\nStory File Name:  %s\n", storyFileName);
  printf("-----------------------------------------\n", storyFileName);

  catarray_t catArray = getCategories(wordsFileName);

  // printf("\n\n **************** %s ******************* \n\n", wordsFileName);

  // for (int i = 0; i < catArray.n; i++) {
  //   printf("%d ... %s \n", i, catArray.arr[i].name);
  //   for (int j = 0; j < catArray.arr[i].n_words; j++)
  //     printf("  %d .. %s \n", j, catArray.arr[i].words[j]);
  // }

  // printf("\n **************** %s ******************* \n", "-");

  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(storyFileName, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // printf("\n ----------- %s ----------- \n\n", storyFileName);

  char *catWords[200];
  int catWordCounts = 0;

  while ((read = getline(&line, &len, fp)) != -1) {

    char *token = strtok(line, " ");
    char *word;

    char *categoryName;

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
        // printf("Inside else If %s \n", token);
        // Call chooseWords functions
        char *oldW =
            (char *)malloc((position_last - position_first) * sizeof(char));

        strncpy(oldW, token + position_first,
                position_last - position_first + 1);
        oldW[position_last - position_first + 1] = '\0';

        // printf("Token %s \n", token);
        // printf("Old Word %s \n", oldW);

        categoryName = strdup(oldW);
        removeChar(categoryName, categoryName[0]);

        // printf("%s - %s \n", oldW, categoryName);

        int categoryNumber = atoi(categoryName);
        // printf("Converted Number %i \n", categoryNumber);

        char *temp = (char *)malloc(20 * sizeof(char));
        sprintf(temp, "%i", categoryNumber);

        // printf("Temp %s \n", temp);

        // printf("%s - %s - %i - %s", oldW, categoryName, categoryNumber,
        // temp);

        getCategories(wordsFileName);

        const char *newW;

        if (strlen(categoryName) == strlen(temp)) {
          // printf("%s - %i. %s \n", oldW, categoryNumber,
          // catWords[categoryNumber-1]);
          newW = catWords[categoryNumber - 1];
        } else {
          newW = chooseWord(oldW, &catArray);
          catWords[catWordCounts] = strdup(newW);
          catWordCounts++;
        }

        // printf("New Word %s \n", newW);

        // printf("%s %s - %s | %s \n ------------------ \n", token, oldW, newW,
        //        replaceWord(token, oldW, newW));
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

  // printf("\n\n ----------- %s ----------- \n\n", "*");

  // printf("\n\n ----------- Test ----------- \n\n", "*");

  // for(int i = 0; i < catWordCounts; i++) {
  //   printf("%i. %s \n", i, catWords[i]);
  // }

  // printf("\n\n ----------- Test ----------- \n\n", "*");

  printf("\n\n");

  fclose(fp);
  if (line)
    free(line);
  exit(EXIT_SUCCESS);
}