
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
struct key {
  char k[40];
  char v[40];
  int count;
};

int binsearch(char *, struct key *, int);

int main() {
  /* Define a studentdata structure */
  struct key keytab[20];
  struct key keyvalues[20];

  FILE *filehandle;
  char line[121];

  char *item;
  char key[40];
  int reccount = 0;
  int k;

  /* Here comes the actions! */
  /* open file */

  filehandle = fopen("words.txt", "r");

  /* Read file line by line */
  int n;
  while (fgets(line, 120, filehandle)) {
    printf("source line %s", line);

    item = strtok(line, ":");
    strcpy(key, item);
    strcpy(keytab[reccount].k, item);

    item = strtok(NULL, "\n");
    strcpy(keytab[reccount].v, item);

    keytab[reccount].count = 0;

    int i = 0;
    struct key *ptr = keytab;

    for (int i = 0; i < reccount; i++, ptr++) {
      // do your thing with the ptr
      // and note that ptr gets increased inside for
      if (strcmp(ptr[i].k, key) == 0) {
        printf("Gotcha!\n");
        keyvalues[i].count++;
        break;
      } else {
        strcpy(keyvalues[i].k, key);
        keyvalues[i].count = 0;
      }
    }
    reccount++;
  }

  /* Close file */

  fclose(filehandle);

  /* Loop through and report on data */

  printf("\n key-value config \n");
  for (k = 0; k < reccount; k++) {
    printf("It is %s %s %d\n", keytab[k].k, keytab[k].v, keytab[k].count);
  }

  printf("\n key-value config \n");
  for (k = 0; k < reccount; k++) {
    printf("It is %s %s %d\n", keyvalues[k].k, keyvalues[k].v,
           keyvalues[k].count);
  }
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n) {
  int cond;
  int low, high, mid;
  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if ((cond = strcmp(word, tab[mid].k)) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}