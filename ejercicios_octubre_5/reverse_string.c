#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void reverse_string_aux(char *original, char *reversed, int position) {
  if (position < 0) {
    return;
  }
  char char_to_concat[] = {*(original + position), 0};
  strcat(reversed, char_to_concat);
  reverse_string_aux(original, reversed, position - 1);
}

char *reverse_string(char *originalString) {
  char *reversed = malloc(strlen(originalString) + 1);
  reversed[0] = '\0';
  reverse_string_aux(originalString, reversed, strlen(originalString) - 1);
  return reversed;
}

int main() {
  char myString[] = "w3resource";
  char *reversed = reverse_string(myString);
  printf("The reverse of the string \"%s\" is \"%s\"\n", myString, reversed);
  free(reversed);
  return 0;
}
