
#include <stdio.h>
#include <string.h>

/* Reading data from the lines of a file, tokenising
it and storing each of the elements from each line
into a structure.  An array os such structures holds
the data as a whole ...
http://www.wellho.net/resources/ex.php?item=c210/lunches.c
*/

/* Sample data lines
#%% Read file into array of structs
5 0 Wednesday Sunny
6 2 Thursday Wet
*/

int main() {
  /* Define a studentdata structure */

  struct key {
    char *word;
    int count;
  };

  struct key keytab[20];

  typedef struct {
    char studentId[10];
    char studentName[80];
    char studentScore[10];
  } studentdata;
  studentdata record[30];
  FILE *filehandle;
  char line[121];

  char *item;
  int reccount = 0;
  int k;

  /* Here comes the actions! */
  /* open file */

  filehandle = fopen("person.dat", "r");

  /* Read file line by line */

  while (fgets(line, 120, filehandle)) {
    printf("source line %s", line);

    item = strtok(line, ",");
    strcpy(record[reccount].studentId, item);

    item = strtok(NULL, ",");
    strcpy(record[reccount].studentName, item);

    item = strtok(NULL, "\n");
    strcpy(record[reccount].studentScore, item);

    reccount++;
  }

  /* Close file */

  fclose(filehandle);

  /* Loop through and report on data */

  printf("\nStudent Record\n");
  for (k = 0; k < reccount; k++) {
    printf("It is %s %s %s\n", record[k].studentId, record[k].studentName,
           record[k].studentScore);
  }
}