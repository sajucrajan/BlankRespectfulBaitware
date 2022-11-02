#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *storyFileName = NULL;
  char *wordsFileName = NULL;

  printf("%s %s %s")

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
}