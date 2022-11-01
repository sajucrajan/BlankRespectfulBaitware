// C program for writing
// struct to file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a struct to read and write
struct person {
  int id;
  char fname[20];
  char lname[20];
};

int main() {
  FILE *fin = fopen("person.dat", "r");
  if (!fin) {
    printf("Can't open file: person.dat\n");
    return 0;
  }
  int i = 0;
  
  char *lineptr = NULL;
  size_t size = 0;

  
  return 0;
}
