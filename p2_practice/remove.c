#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char fileName[] = "./example.txt";
  char buffer[256];
  char toRemove[] = "example";

  FILE *input = fopen(fileName, "r");
  FILE *output = fopen("./removed.txt", "w");
  
  char *current, *found;
  int wordsCount = 0;

  while (fgets(buffer, 256, input)) {
    // If we find the word then delete it.
    if (strstr(buffer, toRemove)) {
      // Start at the beginning of the string.
      current = buffer;
      found = strstr(current, toRemove);
      while(found) {
        // Write all the characters until we reach the found substring.  
        while (current != found) {
          fputc(*current, output);
          current += 1;
        }
        // Skip over the word;
        current += strlen(toRemove);
        // Increment the wordcount.
        wordsCount += 1; 
        // Prepare for the next loop.
        found = strstr(current, toRemove);
      }
      // Write the rest of the characters.
      while(*current != '\0') {
        fputc(*current, output);
        current += 1;
      }
    } else {
      // Write the whole string.
      fputs(buffer, output);
    }

  }
  
  printf("Found the word: %d times\n", wordsCount);
  remove(fileName);
  rename("./removed.txt", fileName);

  fclose(input);
  fclose(output);
  return 0;
}
