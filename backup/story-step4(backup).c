#include "provided.h"
#include "rand_story.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSIZ 128
#define RSIZ 20

int main(int argc, char *argv[]) {
  char *storyFileName = NULL;
  char *wordsFileName = NULL;
  bool isWordReusable = true;
  int expectedArgs = 3;
  int i;

  printf("Argument count=%d\n", argc);

  for (i = 0; i < argc; i++) {
    printf("Argument %s\n", argv[i]);

    if (strcmp(argv[i], "-n") == 0) {
      isWordReusable = false;
      expectedArgs = 4;
      printf("    isWordReusable=TRUE\n");
    }
  }

  printf("Actual Argument count=%d\n", argc);
  printf("Expected Argument count=%d\n", expectedArgs);

  if (argc != expectedArgs) {
    printf("Required argument(s) missing.\n");
    fprintf(stderr, "Usage: %s [-n] storyFileName wordsFileName\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (argc == 3) {
    storyFileName = argv[1];
    wordsFileName = argv[2];
  }

  if (argc == 4) {
    storyFileName = argv[2];
    wordsFileName = argv[3];
  }

  printf("\nisWordResuable:  %d\n", isWordReusable);
  printf("\nStory File Name:  %s\n", storyFileName);
  printf("\nWords File Name:  %s\n", wordsFileName);
  printf("-----------------------------------------\n");

  char *lines[RSIZ];
  FILE *fptr = NULL;
  int l = 0;
  int tot = 0, index = -1;
  fptr = fopen(wordsFileName, "r");
  char *buffer = 0;
  size_t buflen = 0;

  for (int i = 0; i < RSIZ && getline(&buffer, &buflen, fptr) != -1; i++) {
    buffer[strcspn(buffer, "\n")] = '\0';
    lines[i] = buffer;
    buffer = 0;
    buflen = 0;
    tot = i;
  }
  free(buffer);

  // while (fgets(lines[l], LSIZ, fptr)) {
  //   //lines[l][strlen(lines[l]) - 1] = '\0';
  //   l++;
  // }
  fclose(fptr);

  // // tot = l;
  printf("\n The content of the file %s  are : \n", wordsFileName);
  for (l = 0; l <= tot; ++l) {
    printf(" %s \n", lines[l]);
  }
  printf("\n");

  // printf("before use function call %d \n", tot);
  // Strfun(lines, tot);
  // printf("after use function call \n");

  // // delete an element from array with line animal:dog
  // for (l = 0; i < tot; l++) {
  //   if (strcmp(lines[l], "animal:dog") == 0) {
  //     index = l;
  //     break;
  //   }
  // }

  // printf("\n index to be deleted from array %d \n", index);
  // if (index != -1) {
  //   // shift all the element from index+1 by one position to the left
  //   for (l = index; l < tot - 1; l++) {
  //     strcpy(lines[l], lines[l + 1]);
  //   }

  //   printf("\n New Array : \n");
  //   for (l = 0; l < tot - 1; l++) {
  //     printf("%s \n", lines[l]);
  //   }
  // } else {
  //   printf("Element Not Found\n");
  // }

  catarray_t catArray = getCategoriesFromArray(lines, tot);

  //  catarray_t catArray = getCategories(wordsFileName);

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

  /* Define a temporary variable */
  char outputline[255];

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
      const char *newW;

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

        // getCategories(wordsFileName);
        getCategoriesFromArray(lines, tot);

        // const char *newW;

        if (strlen(categoryName) == strlen(temp)) {
          // printf("%s - %i. %s \n", oldW, categoryNumber,
          // catWords[categoryNumber-1]);
          newW = catWords[categoryNumber - 1];
        } else {
          newW = chooseWord(oldW, &catArray);
          catWords[catWordCounts] = strdup(newW);
          catWordCounts++;
        }

        // printf("New Word %s %s %s \n",  oldW, newW);
        //-- ng

        if (!isWordReusable) {

          // delete an element from array with line animal:dog
          for (l = 0; i <= tot; l++) {
            // if (strcmp(lines[l], newW) == 0) {
            if (strstr(lines[l], newW) != NULL) {
              index = l;
              break;
            }
          }
          printf("\n string %s to be deleted from array index %d \n", newW,
                 index);
          if (index != -1) {
            // shift all the element from index+1 by one position to the left
            for (l = index; l <= tot-1; l++) {
              strcpy(lines[l], lines[l + 1]);
            }

            strcpy(lines[l], "");

            printf("\n New Array : \n");
            for (l = 0; l <= tot ; l++) {
              printf("%s \n", lines[l]);
            }
            tot--;

          } else {
            printf("Element Not Found\n");
          }
        }
        // -- ng

        // printf("%s %s - %s | %s \n ------------------ \n", token, oldW, newW,
        //        replaceWord(token, oldW, newW));
        word = replaceWord(token, oldW, newW);

        // printf(" remove this string %20s from array \n", token);
      } else {
        // word = malloc(strlen(token));
        word = token;
      }

      // printf("test me New Word %s \n", newW);

      // printf("%s | %d %d \n", token, position_first, position_last);
      // printf("%s \n", word);

      token = strtok(NULL, " ");

      // printf("%s", word);
      strcat(outputline, word);
      if (token != NULL) {
        // printf(" ");
        strcat(outputline, " ");
      }
    }
  }

  /* Display the concatenated strings */
  printf("output line is: \n %s \n", outputline);

  // ng
  if (!isWordReusable) {
    // open the file for writing
    FILE *fptrw = fopen(wordsFileName, "w");
    if (fptrw == NULL) {
      printf("Error opening the file %s", wordsFileName);
      return -1;
    }
    // write to the text file
    printf("\n write back to the file : \n");
    for (l = 0; l <= tot; l++) {
      fprintf(fptrw, "%s\n", lines[l]);
    }

    // close the file
    fclose(fptrw);
  }
  // ng

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