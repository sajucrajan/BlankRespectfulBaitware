#include "provided.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  char str1[100];
  char newString[10][10];
  int i, j, ctr;

  fp = fopen(fileName, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  while ((read = getline(&line, &len, fp)) != -1) {
    // printf("line length %zu:\n", read);
    // printf("%s", line);

    char *token = strtok(line, " ");

    // loop through the string to extract all other tokens
    while (token != NULL) {
      
      char *position_ptr_first = strchr(token, '_');
      char *position_ptr_last = strrchr(token, '_');
      
      int position_first = (position_ptr_first == NULL ? -1 : position_ptr_first - token);
      int position_last = (position_ptr_last == NULL ? -1 : position_ptr_last - token);
      
      int count = 0;

      if (position_first != -1) {
        count++;
      }

      printf("%s | %d %d \n", token, position_first, position_last);
      
      token = strtok(NULL, " ");
    }

    // j = 0;
    // ctr = 0;
    // for (i = 0; i <= (strlen(line)); i++) {
    //   // if space or NULL found, assign NULL into newString[ctr]
    //   if (line[i] == ' ' || line[i] == '\0') {
    //     newString[ctr][j] = '\0';
    //     ctr++; // for next word
    //     j = 0; // for next word, init index to 0
    //   } else {
    //     newString[ctr][j] = line[i];
    //     j++;
    //   }
    // }

    // printf("\n Strings or words after split by space are :\n");
    // for (i = 0; i < ctr; i++)
    //   printf(" %s\n", newString[i]);
  }

  fclose(fp);
  if (line)
    free(line);
  exit(EXIT_SUCCESS);
}