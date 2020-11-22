#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef unsigned char BOOL;

#define TRUE 1
#define FALSE 0

int main() {
  char fileName[] = "./example.txt";
  char buffer[256];

  FILE *file = fopen(fileName, "r");

  if (file == NULL) {
    printf("File could not be read\n");
    return 0;
  } else {
    printf("File was opened correctly\n");
  }

  int charCount = 0, wordCount = 0, lineCount = 0; 
  while(fgets(buffer, 256, file)) {
    printf("Read from file: %s", buffer);
    // Ignore the newline.
    charCount += strlen(buffer) - 1;
    lineCount += 1;

    // Count words.
    int i = 0;
    BOOL foundSpace = FALSE;
    BOOL foundChar = FALSE;

    while(buffer[i] != '\0') {
      if(isspace(buffer[i])) {
        foundSpace = TRUE;
      } else if (foundSpace){
        wordCount += 1; 
        foundSpace = FALSE;
      } else {
        foundChar = TRUE;
      }

      i++;
    }

    if (foundChar) {
      wordCount += 1;
    }

  }

  printf("Found %d chars, %d words and %d lines\n", charCount, wordCount, lineCount);

  fclose(file);

  return 0;
}
