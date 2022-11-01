#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
int main(void) {
  int N = 300;
  int L = 1000;
  char Nseq[N][L];
  FILE *myfile;
  char *token;
  const char s[2] = ",";
  char *line;
  int len;
  char *filename = "person.dat";
  int err;
  struct stat st;
  int n = 0;
  err = stat(filename, &st);
  if (err < 0) {
    printf("could not stat file %s", filename);
    exit(1);
  }
  len = st.st_size + 1;
  line = malloc(len);
  myfile = fopen(filename, "r");
  if (myfile == NULL) {
    printf("could not open file %s", filename);
    exit(1);
  }
  while (fgets(line, len, myfile) != NULL) {
    token = strtok(line, s);
    while (token != NULL) {
      strcpy(Nseq[n], token);
      printf("%s \n ", token);
      token = strtok(NULL, s);
      n++;
    }
  }
  fclose(myfile);
  return 0;
}