
void removeChar(char * str, char charToRemmove){
  int i, j;
  int len = strlen(str);

  // printf("Inside %s %c\n", str, charToRemmove);
  
  for(i=0; i<len; i++)
  {
      // printf("%c \n", str[i]);
      if(str[i] == charToRemmove)
      {
          // printf("Match \n");
          for(j=i; j<len; j++)
          {
              str[j] = str[j+1];
          }
          len--;
          i--;
      }
  }
}
