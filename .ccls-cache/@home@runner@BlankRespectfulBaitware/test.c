#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  int a = atoi("991a993");

  char *temp = (char *)malloc(20 * sizeof(char));
  ;

  sprintf(temp, "%i", a);

  printf("%i | %i - %d \n", a, strlen("991a993"), strlen(temp));
}